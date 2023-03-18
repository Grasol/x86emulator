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




