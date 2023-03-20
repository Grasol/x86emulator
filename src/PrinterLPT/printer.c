#include "printer.h"

Printer* printer_init(char *name, uint64_t lpt_addr, size_t line_size, 
    double write_timeout, double busy_time) {
  
  Printer *printer = malloc(sizeof(Printer));
  if (!printer) {
    goto memory_error;
  }

  printer->name = name;
  printer->lpt_addr = lpt_addr;
  printer->line = malloc(line_size + 2);
  if (!printer->line) {
    goto memory_error;
  }

  printer->line_size = line_size;
  printer->line_fill = 0;
  printer->emulator_write_check = 0.0;
  printer->emulator_write_timeout = write_timeout;
  printer->emulator_busy_time = busy_time;

  printer->data_port = 0;
  printer->status_port = 0;
  printer->control_port = 0;

  printer->temporary_off_strobe = false;

  return printer;

  memory_error:
  fprintf(stderr, "Memory error\n");
  exit(1);
}


void printer_update(Printer *printer) {
  size_t lpt_addr = printer->lpt_addr;
  char *line = printer->line;
  size_t line_fill = printer->line_fill;

  uint8_t data_port = PHYMEM_le_load_byte(printer->phy_mem, lpt_addr);
  uint8_t status_port = printer->status_port & (~PRINTER_STATUS_ACK);
  uint8_t control_port = PHYMEM_le_load_byte(printer->phy_mem, lpt_addr + 2);
  bool write = false;




  if (control_port & PRINTER_CONTROL_SELECT_PRINTER) {
    if (control_port & PRINTER_CONTROL_STROBE & !printer->temporary_off_strobe) {
      printer->temporary_off_strobe = true;
      printf("PRINT1: %i\n", line_fill);
      if (status_port & PRINTER_STATUS_BUSY) { // not busy 
        line[line_fill] = data_port;
        ++line_fill;
        printf("PRINT2: %i\n", line_fill);

        if (data_port == '\n') {
          write = true;
        }
        else if (data_port == '\r') {
          if (control_port & PRINTER_CONTROL_AUTO_LINEFEED) {
            line[line_fill] = '\n';
            ++line_fill;
          }
        }

        printer->status_port &= ~PRINTER_STATUS_BUSY; // printer busy 
        printer->emulator_write_check = clock();
        printf("PRINT3: %d\n", printer->emulator_write_check);
      }
    }
    else {
      printer->temporary_off_strobe = false;
    }

    if (!(control_port & PRINTER_CONTROL_INIT)) {
      size_t real_size = printer->line_size + 2;
      for (size_t i = 0; i < real_size; ++i) {
        line[i] = 0;
      }

      line_fill = 0;
      printer->emulator_write_check = 0.0;
      status_port = PRINTER_STATUS_BUSY;
    }

    status_port |= PRINTER_STATUS_SELECT;
  }

  if (printer->emulator_write_check != 0.0) {
    printf("PRINT4: %i\n", line_fill);
    if (line_fill == printer->line_size) {
      write = true;
    }

    clock_t tmp_check = clock() - printer->emulator_write_check;  
    if (tmp_check >= printer->emulator_busy_time) {
      status_port |= PRINTER_STATUS_BUSY; // not busy
      status_port |= PRINTER_STATUS_ACK;
    }

    if (tmp_check >= printer->emulator_write_timeout) {
      write = true;
      printer->emulator_write_check = 0.0;
    }
  }

  if (write) {
    FILE *f = open_file(printer->name, "a", NULL);
    fwrite(line, 1, line_fill, f);
    fclose(f);

    line_fill = 0;
  }

  printer->line_fill = line_fill;

  printer->data_port = data_port;
  printer->status_port = status_port;
  printer->control_port = control_port;
  PHYMEM_le_store_byte(printer->phy_mem, lpt_addr + 1, status_port);  
  return;
}