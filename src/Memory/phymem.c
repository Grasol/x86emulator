#include "phymem.h"



PhyMem* PhysicalMemoryInit(size_t max, uint8_t *data, size_t data_size) {
  PhyMem *phy_mem = malloc(sizeof(PhyMem));
  if (phy_mem == NULL) {
    goto mem_error;
  }

  phy_mem->sz = (max & ALLOCATION_MASK);

  uint8_t *memory = malloc(sizeof(uint8_t) * ALLOCATION_STEP);
  if (memory == NULL) {
    goto mem_error;
  }

  printf("Reserved %I64u bytes memory\n", phy_mem->sz);

  memset(memory, 0, ALLOCATION_STEP);
  phy_mem->memory = memory;
  phy_mem->dynamic_allocation_step = ALLOCATION_STEP;
  printf("Allocated %I64u bytes memory\n", phy_mem->dynamic_allocation_step);

  if (data != NULL) {
    PHYMEM_allocation_check(phy_mem, data_size);
    memcpy(phy_mem->memory, data, data_size);
  }

  return phy_mem;

  mem_error:
  fprintf(stderr, "Memory error\n");
  exit(MEM_ERR);
}


void PHYMEM_allocation_check(PhyMem *phy_mem, uint64_t physical_addr) {
  size_t check_physical = physical_addr & ALLOCATION_MASK;
  if (phy_mem->sz - phy_mem->dynamic_allocation_step == 0) {
    return;
  }

  if (phy_mem->dynamic_allocation_step >= check_physical) {
    return;
  }

  phy_mem->memory = realloc(phy_mem->memory, sizeof(uint8_t) * check_physical);
  if (phy_mem->memory == NULL) {
    goto mem_error;
  }

  memset(phy_mem->memory + phy_mem->dynamic_allocation_step, 0, check_physical);
  phy_mem->dynamic_allocation_step = check_physical;
  printf("Allocated %I64u bytes memory\n", phy_mem->dynamic_allocation_step);

  return;

  mem_error:
  fprintf(stderr, "Memory error\n");
  exit(MEM_ERR);
}



uint8_t PHYMEM_le_load_byte(PhyMem *phy_mem, uint64_t physical_addr) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  if (physical_addr >= phy_mem->sz) {
    return 0xff;
  }

  return phy_mem->memory[physical_addr];
}

uint16_t PHYMEM_le_load_word(PhyMem *phy_mem, uint64_t physical_addr) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  uint16_t res = 0xffff;
  if (physical_addr >= phy_mem->sz) {
    return res;
  }

  uint16_t b0 = (uint16_t)phy_mem->memory[physical_addr];
  uint16_t b1 = (uint16_t)phy_mem->memory[physical_addr + 1];

  res = (b1 << 8) | b0;
  return res;
}

uint32_t PHYMEM_le_load_dword(PhyMem *phy_mem, uint64_t physical_addr) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  uint32_t res = 0xffffffff;
  if (physical_addr >= phy_mem->sz) {
    return res;
  }

  uint32_t b0 = (uint32_t)phy_mem->memory[physical_addr];
  uint32_t b1 = (uint32_t)phy_mem->memory[physical_addr + 1];
  uint32_t b2 = (uint32_t)phy_mem->memory[physical_addr + 2];
  uint32_t b3 = (uint32_t)phy_mem->memory[physical_addr + 3];

  res = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
  return res;
}

uint64_t PHYMEM_le_load_qword(PhyMem *phy_mem, uint64_t physical_addr) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  uint64_t res = 0xffffffffffffffff;
  if (physical_addr >= phy_mem->sz) {
    return res;
  }

  uint64_t b0 = (uint64_t)phy_mem->memory[physical_addr];
  uint64_t b1 = (uint64_t)phy_mem->memory[physical_addr + 1];
  uint64_t b2 = (uint64_t)phy_mem->memory[physical_addr + 2];
  uint64_t b3 = (uint64_t)phy_mem->memory[physical_addr + 3];
  uint64_t b4 = (uint64_t)phy_mem->memory[physical_addr + 4];
  uint64_t b5 = (uint64_t)phy_mem->memory[physical_addr + 5];
  uint64_t b6 = (uint64_t)phy_mem->memory[physical_addr + 6];
  uint64_t b7 = (uint64_t)phy_mem->memory[physical_addr + 7];

  res = (b7 << 56) | (b6 << 48) | (b5 << 40) | (b4 << 32) | 
        (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
  return res;
}



void PHYMEM_le_store_byte(PhyMem *phy_mem, uint64_t physical_addr, uint8_t data) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  if (physical_addr >= phy_mem->sz) {
    return;
  }

  phy_mem->memory[physical_addr] = data;
  return;
}

void PHYMEM_le_store_word(PhyMem *phy_mem, uint64_t physical_addr, uint16_t data) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  if (physical_addr >= phy_mem->sz) {
    return;
  }

  phy_mem->memory[physical_addr] =      data & 0xff;
  phy_mem->memory[physical_addr + 1] = (data >> 8) & 0xff;
  return;
}

void PHYMEM_le_store_dword(PhyMem *phy_mem, uint64_t physical_addr, uint32_t data) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  if (physical_addr >= phy_mem->sz) {
    return;
  }

  phy_mem->memory[physical_addr] =      data & 0xff;
  phy_mem->memory[physical_addr + 1] = (data >> 8) & 0xff;
  phy_mem->memory[physical_addr + 2] = (data >> 16) & 0xff;
  phy_mem->memory[physical_addr + 3] = (data >> 24) & 0xff;
  return;
}

void PHYMEM_le_store_qword(PhyMem *phy_mem, uint64_t physical_addr, uint64_t data) {
  PHYMEM_allocation_check(phy_mem, physical_addr);
  if (physical_addr >= phy_mem->sz) {
    return;
  }

  phy_mem->memory[physical_addr] =      data & 0xff;
  phy_mem->memory[physical_addr + 1] = (data >> 8) & 0xff;
  phy_mem->memory[physical_addr + 2] = (data >> 16) & 0xff;
  phy_mem->memory[physical_addr + 3] = (data >> 24) & 0xff;
  phy_mem->memory[physical_addr + 4] = (data >> 32) & 0xff;
  phy_mem->memory[physical_addr + 5] = (data >> 40) & 0xff;
  phy_mem->memory[physical_addr + 6] = (data >> 48) & 0xff;
  phy_mem->memory[physical_addr + 7] = (data >> 56) & 0xff;
  return;
}