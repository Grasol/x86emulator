/*
 * This file is part of x86emulator-by-Grasol
 *
 * x86emulator-by-Grasol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * x86emulator-by-Grasol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with x86emulator-by-Grasol.  If not, see <http://www.gnu.org/licenses/>.
*/

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

  memset(printer->line, 0, line_size + 2);
  printer->line_size = line_size;
  printer->line_fill = 0;
  printer->line_cursor = 0;
  printer->emulator_write_timer = 0.0;
  printer->emulator_write_default_timeout = write_timeout;
  printer->emulator_busy_check = 0;
  printer->emulator_busy_default_no = busy_time;

  printer->data_port = 0;
  printer->status_port = 0;
  printer->control_port = 0;

  return printer;

  memory_error:
  fprintf(stderr, "Memory error\n");
  exit(1);
}

void printer_update(Printer *printer) {
  size_t lpt_addr = printer->lpt_addr;
  char *line = printer->line;
  size_t line_fill = printer->line_fill;
  size_t line_cursor = printer->line_cursor;
  double emulator_write_timer = printer->emulator_write_timer;
  int emulator_busy_check = printer->emulator_busy_check;

  uint8_t data_port = PHYMEM_le_load_byte(printer->phy_mem, lpt_addr);
  uint8_t status_port = printer->status_port & (~PRINTER_STATUS_ACK);
  uint8_t control_port = PHYMEM_le_load_byte(printer->phy_mem, lpt_addr + 2);
 

  status_port &= ~PRINTER_STATUS_ACK;
  if (printer->emulator_busy_check == 0) {
    status_port |= PRINTER_STATUS_BUSY;
  }
  else {
    status_port &= ~PRINTER_STATUS_BUSY; 
  }

  /*
   * control port service
   */
  if (control_port & PRINTER_CONTROL_SELECT_PRINTER) {
    status_port |= PRINTER_STATUS_SELECT;
    if (!(control_port & PRINTER_CONTROL_INIT)) {
      size_t real_size = printer->line_size + 2;
      for (size_t i = 0; i < real_size; ++i) {
        line[i] = 0;
      }

      line_fill = 0;
      line_cursor = 0;
      emulator_write_timer = 0.0;
      emulator_busy_check = 0;
    }
    else if (control_port & PRINTER_CONTROL_STROBE) { // character on data port
      if (emulator_busy_check == 0) { // printer is not busy
        if (data_port == '\r') { // TODO: back to beginning of line in file 
          if (control_port & PRINTER_CONTROL_AUTO_LINEFEED) {
            // \r is triggering \n
            line[line_cursor] = '\n';
            ++line_cursor;
          }
          else {
            line_cursor = 0;
          }
        }
        else {
          line[line_cursor] = data_port;
          ++line_cursor;
        }

        ++line_fill;

        emulator_busy_check = -1; // wait state of clearing STROBE flag
        emulator_write_timer = (double)clock();
        status_port |= PRINTER_STATUS_ACK;
      } 
    }
    else {
      if (emulator_busy_check == -1) {
        emulator_busy_check = printer->emulator_busy_default_no;
      }
      else if (emulator_busy_check > 0) {
        --emulator_busy_check;
      }
    }
  }
  else {
    status_port &= ~PRINTER_STATUS_SELECT;
  }

  /*
   * write service
   */
  bool write = false;
  bool new_line = false;
  double temp_clock = (double)clock() - emulator_write_timer;
  if (line_fill >= printer->line_size) {
    write = true;
    new_line = true;
  }

  if (line_fill != 0) {
    if (line[line_cursor - 1] == '\n') {
      write = true;
      new_line = true;
    }
  }

  if (emulator_write_timer != 0.0) {
    if ((temp_clock) >= printer->emulator_write_default_timeout) {
      write = true;
    }
  }

  if (write) {
    FILE *f = open_file(printer->name, "a", NULL);
    fwrite(line, 1, line_cursor, f);
    fclose(f);

    emulator_write_timer = 0.0;
    memset(line, 0, printer->line_size + 2);
    line_cursor = 0;
    if (new_line) {
      line_fill = 0;    
    }
  }

  printer->line_fill = line_fill;
  printer->line_cursor = line_cursor;
  printer->emulator_write_timer = emulator_write_timer;
  printer->emulator_busy_check = emulator_busy_check;

  printer->data_port = data_port;
  printer->status_port = status_port;
  printer->control_port = control_port;
  PHYMEM_le_store_byte(printer->phy_mem, lpt_addr + 1, status_port);  
  return;
}