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

#include "interrupt.h"

void INT_set_interrupt(CPUx86 *cpu, int_signal) {
  switch (cpu->interrupt_service) {
    case NO_INTERRUPT: {
      cpu->interrupt_service = RUN_INTERRUPT;
      cpu->interrupt_signal = int_signal & 0xff;
      break;
    }
    case RUN_INTERRUPT: {
      if (cpu->interrupt_signal == INTERRUPT_DF) {
        cpu->interrupt_service = TRIPLE_FAULT
      }
      else {
        cpu->interrupt_signal = INTERRUPT_DF;
      }

      break;
    }
    default: {
      cpu->interrupt_service = TRIPLE_FAULT;
    }

  return;
}




