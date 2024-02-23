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

#include "paging.h"

uint64_t PAG_get_physical_addr(CPUx86 *cpu, uint32_t linear_addr) {
  uint64_t physical_address = 0;

  switch (cpu->paging_mode) {
    case PAGING_NO: {
      physical_address = linear_addr;
      break;
    }

    // TODO: 32bit and PAE paging 
  }

  return physical_address;
}







