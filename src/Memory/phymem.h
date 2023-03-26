#pragma once

#include "../includes.h"

#define ALLOCATION_STEP 0x01000000 
#define ALLOCATION_MASK 0xff000000

struct PhysicalMemory {
  uint8_t *memory;
  size_t sz;

  size_t dynamic_allocation_step; // 16MB step
};
typedef struct PhysicalMemory PhyMem;

PhyMem* PHYMEM_init(size_t max, uint8_t *data, size_t data_size);
void PHYMEM_allocation_check(PhyMem *phy_mem, uint64_t physical_addr);

uint8_t  PHYMEM_le_load_byte(PhyMem *phy_mem, uint64_t physical_addr);
uint16_t PHYMEM_le_load_word(PhyMem *phy_mem, uint64_t physical_addr);
uint32_t PHYMEM_le_load_dword(PhyMem *phy_mem, uint64_t physical_addr);
uint64_t PHYMEM_le_load_qword(PhyMem *phy_mem, uint64_t physical_addr);
/*uint8_t  PHYMEM_be_load_byte(PhyMem *phy_mem, uint64_t addr);
uint16_t PHYMEM_be_load_word(PhyMem *phy_mem, uint64_t addr);
uint32_t PHYMEM_be_load_dword(PhyMem *phy_mem, uint64_t addr);
uint64_t PHYMEM_be_load_qword(PhyMem *phy_mem, uint64_t addr);*/

void PHYMEM_le_store_byte(PhyMem *phy_mem, uint64_t physical_addr, uint8_t data);
void PHYMEM_le_store_word(PhyMem *phy_mem, uint64_t physical_addr, uint16_t data);
void PHYMEM_le_store_dword(PhyMem *phy_mem, uint64_t physical_addr, uint32_t data);
void PHYMEM_le_store_qword(PhyMem *phy_mem, uint64_t physical_addr, uint64_t data);
/*void PHYMEM_be_store_byte(PhyMem *phy_mem, uint64_t addr, uint8_t data);
void PHYMEM_be_store_word(PhyMem *phy_mem, uint64_t addr, uint16_t data);
void PHYMEM_be_store_dword(PhyMem *phy_mem, uint64_t addr, uint32_t data);
void PHYMEM_be_store_qword(PhyMem *phy_mem, uint64_t addr, uint64_t data);*/


