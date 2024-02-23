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


argp_option parse_switch(char *value);
int parse_value(Argp *argp, char *value, argp_option option);
void parse_argument(int argc, char **argv, Argp *argp);
void print_help();



struct EmulatorState {
  CPUx86 *cpu;
  PhyMem *phy_mem;
  Printer *printer;

  bool debug_mode;
  bool quit;
};
typedef struct EmulatorState Emulator;

#define DEBUG_LINE_SIZE 64

void enter_debug_mode(Emulator *emulator);




