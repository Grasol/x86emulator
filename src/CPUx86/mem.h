#pragma once


int get_physical_addr(CPUx86 *cpu, int segment, uint64_t effective_addr, uint64_t *phy_addr);

int load_byte(CPUx86 *cpu, int segment, uint64_t effective_addr, uint8_t *data);
int load_word(CPUx86 *cpu, int segment, uint64_t effective_addr, uint16_t *data);
int load_dword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint32_t *data);
int load_qword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint64_t *data);

int store_byte(CPUx86 *cpu, int segment, uint64_t effective_addr, uint8_t data);
int store_word(CPUx86 *cpu, int segment, uint64_t effective_addr, uint16_t data);
int store_dword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint32_t data);
int store_qword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint64_t data);


