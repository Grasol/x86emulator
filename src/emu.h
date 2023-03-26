#pragma once

#include "includes.h"
#include "cpu.h"
#include "phymem.h"
#include "printer.h"


struct Argp {
  size_t memory_size;
  char *memory_dump;
  uint64_t breakpoint_addr; // -1 when breakpoint_addr turn off

  bool help;
  bool debug_mode;
  bool xchg_breakpoint;
};
typedef struct Argp Argp;

#define ARGP_OPTIONS 6
enum argp_option {
  HELP,
  MEMORY_SIZE,
  MEMORY_DUMP,
  BREAKPOINT_ADDR,
  DEBUG_MODE,
  XCHG_BREAKPOINT,
};
typedef enum argp_option argp_option;

struct Switch_option {
  char *long_name;
  char *short_name;
  char *values;
  char *description;
  argp_option option;
};
typedef struct Switch_option argswitch_t;




struct EmulatorState {
  CPUx86 *cpu;
  PhyMem *phy_mem;
  Printer *printer;
};
typedef struct EmulatorState Emulator;






