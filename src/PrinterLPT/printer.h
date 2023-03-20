#pragma once
#include "includes.h" 

#include "open_file.h"
#include "phymem.h"


#define LPT1_PRINTER_NAME "printer_lpt1.txt"
#define LPT1_ADDR 0x3bc
#define LPT2_PRINTER_NAME "printer_lpt2.txt"
#define LPT2_ADDR 0x378
#define LPT3_PRINTER_NAME "printer_lpt3.txt"
#define LPT3_ADDR 0x278 

#define PRINTER_DEFAULT_SIZE_LINE 80
#define PRINTER_EMULATOR_WRITE_TIMEOUT 5000.0
#define PRINTER_EMULATOR_BUSY_TIME 1000.0

struct Printer {
  PhyMem *phy_mem;
  char *name;
  uint64_t lpt_addr;

  char *line;
  /*
   * real line must be 2 char greater than agreed size (line_size)
   */
  size_t line_size;
  size_t line_fill;
  clock_t emulator_write_check;
  double emulator_write_timeout;
  double emulator_busy_time;

  uint8_t data_port;
  uint8_t status_port;
  uint8_t control_port;

  bool temporary_off_strobe;
};
typedef struct Printer Printer;

#define PRINTER_STATUS_BUSY      0x80 // signal inverted 
#define PRINTER_STATUS_ACK       0x40 
#define PRINTER_STATUS_PAPER_OUT 0x20
#define PRINTER_STATUS_SELECT    0x10
#define PRINTER_STATUS_ERROR     0x08

#define PRINTER_CONTROL_SELECT_PRINTER 0x08 
#define PRINTER_CONTROL_INIT           0x04 // signal inverted
#define PRINTER_CONTROL_AUTO_LINEFEED  0x02 
#define PRINTER_CONTROL_STROBE         0x01 

Printer* printer_init(char *name, uint64_t lpt_addr, size_t line_size, 
    double write_timeout, double busy_time);

void printer_update(Printer *printer);

