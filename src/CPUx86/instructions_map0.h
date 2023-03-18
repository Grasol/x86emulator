#pragma once
#include "../includes.h"

#include "cpu.h"

#define XOR2(v) ((v ^ (v >> 1)) & 0x1)
#define CARRY_CHAIN(a, b, r) ((a & b) | (~r & (a | b)))
#define BORROW_CHAIN(a, b, r) ((r & (~a | b)) | (~a & b))
#define CONDITIONAL_FLAG(v, f) (v ? f : 0)

#define PARITY(v) ((PARITY_TAB[(v & 0xe0) >> 5] >> (v % 32)) & 0x1)
extern uint32_t PARITY_TAB[8];
  
void call_instruction_map0(CPUx86 *cpu);

uint32_t generate_flags_add_byte(uint16_t src1, uint16_t src2, uint16_t res);
uint32_t generate_flags_add_word(uint32_t src1, uint32_t src2, uint32_t res);
uint32_t generate_flags_add_dword(uint64_t src1, uint64_t src2, uint64_t res);

void x86_00_ADD_B(CPUx86 *cpu);
void x86_01_ADD_W(CPUx86 *cpu);
void x86_01_ADD_D(CPUx86 *cpu);
void x86_02_ADD_B(CPUx86 *cpu);
void x86_03_ADD_W(CPUx86 *cpu);
void x86_03_ADD_D(CPUx86 *cpu);
void x86_04_ADD_B(CPUx86 *cpu);
void x86_05_ADD_W(CPUx86 *cpu);
void x86_05_ADD_D(CPUx86 *cpu);

void x86_10_ADC_B(CPUx86 *cpu);
void x86_11_ADC_W(CPUx86 *cpu);
void x86_11_ADC_D(CPUx86 *cpu);
void x86_12_ADC_B(CPUx86 *cpu);
void x86_13_ADC_W(CPUx86 *cpu);
void x86_13_ADC_D(CPUx86 *cpu);
void x86_14_ADC_B(CPUx86 *cpu);
void x86_15_ADC_W(CPUx86 *cpu);
void x86_15_ADC_D(CPUx86 *cpu);

void x86_86_XCHG_B(CPUx86 *cpu);
void x86_87_XCHG_W(CPUx86 *cpu);
void x86_87_XCHG_D(CPUx86 *cpu);
void x86_88_MOV_B(CPUx86 *cpu);
void x86_89_MOV_W(CPUx86 *cpu);
void x86_89_MOV_D(CPUx86 *cpu);
void x86_8A_MOV_B(CPUx86 *cpu);
void x86_8B_MOV_W(CPUx86 *cpu);
void x86_8B_MOV_D(CPUx86 *cpu);

void x86_90_XCHG_W(CPUx86 *cpu);
void x86_90_XCHG_D(CPUx86 *cpu);

void x86_B0_MOV_B(CPUx86 *cpu);
void x86_B8_MOV_W(CPUx86 *cpu);
void x86_B8_MOV_D(CPUx86 *cpu);

void x86_E9_NEAR_JMP_REL16(CPUx86 *cpu);
void x86_E9_NEAR_JMP_REL32(CPUx86 *cpu);
void x86_EB_SHORT_JMP_REL8(CPUx86 *cpu);