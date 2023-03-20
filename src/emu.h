#pragma once

#include "includes.h"
#include "cpu.h"
#include "phymem.h"
#include "printer.h"

struct EmulatorState {
  CPUx86 *cpu;
  PhyMem *phy_mem;
  Printer *printer;
};
typedef struct EmulatorState Emulator;





