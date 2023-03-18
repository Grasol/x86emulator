#pragma once
#include "includes.h"

#pragma once

#include "cpu.h"

uint64_t PAG_get_physical_addr(CPUx86 *cpu, uint32_t linear_addr);