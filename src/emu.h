#pragma once

#include "includes.h"
#include "cpu.h"
#include "phymem.h"

struct EmulatorState {
  CPUx86 *cpu;
  PhyMem *phy_mem;
};
typedef struct EmulatorState Emulator;





