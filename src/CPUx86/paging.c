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







