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
uint32_t generate_flags_sub_byte(uint16_t src1, uint16_t src2, uint16_t res);
uint32_t generate_flags_sub_word(uint32_t src1, uint32_t src2, uint32_t res);
uint32_t generate_flags_sub_dword(uint64_t src1, uint64_t src2, uint64_t res);
uint32_t generate_flags_bitlogic_byte(uint8_t res);
uint32_t generate_flags_bitlogic_word(uint16_t res);
uint32_t generate_flags_bitlogic_dword(uint32_t res);
uint32_t generate_flags_inc_byte(uint8_t src1, uint8_t res);
uint32_t generate_flags_inc_word(uint16_t src1, uint16_t res);
uint32_t generate_flags_inc_dword(uint32_t src1, uint32_t res);
uint32_t generate_flags_dec_byte(uint8_t src1, uint8_t res);
uint32_t generate_flags_dec_word(uint16_t src1, uint16_t res);
uint32_t generate_flags_dec_dword(uint32_t src1, uint32_t res);

void x86_00_ADD_B(CPUx86 *cpu);
void x86_01_ADD_W(CPUx86 *cpu);
void x86_01_ADD_D(CPUx86 *cpu);
void x86_02_ADD_B(CPUx86 *cpu);
void x86_03_ADD_W(CPUx86 *cpu);
void x86_03_ADD_D(CPUx86 *cpu);
void x86_04_ADD_B(CPUx86 *cpu);
void x86_05_ADD_W(CPUx86 *cpu);
void x86_05_ADD_D(CPUx86 *cpu);
void x86_08_OR_B(CPUx86 *cpu);
void x86_09_OR_D(CPUx86 *cpu);
void x86_09_OR_W(CPUx86 *cpu);
void x86_0A_OR_B(CPUx86 *cpu);
void x86_0B_OR_D(CPUx86 *cpu);
void x86_0B_OR_W(CPUx86 *cpu);
void x86_0C_OR_B(CPUx86 *cpu);
void x86_0D_OR_D(CPUx86 *cpu);
void x86_0D_OR_W(CPUx86 *cpu);

void x86_10_ADC_B(CPUx86 *cpu);
void x86_11_ADC_W(CPUx86 *cpu);
void x86_11_ADC_D(CPUx86 *cpu);
void x86_12_ADC_B(CPUx86 *cpu);
void x86_13_ADC_W(CPUx86 *cpu);
void x86_13_ADC_D(CPUx86 *cpu);
void x86_14_ADC_B(CPUx86 *cpu);
void x86_15_ADC_W(CPUx86 *cpu);
void x86_15_ADC_D(CPUx86 *cpu);
void x86_18_SBB_B(CPUx86 *cpu);
void x86_19_SBB_D(CPUx86 *cpu);
void x86_19_SBB_W(CPUx86 *cpu);
void x86_1A_SBB_B(CPUx86 *cpu);
void x86_1B_SBB_D(CPUx86 *cpu);
void x86_1B_SBB_W(CPUx86 *cpu);
void x86_1C_SBB_B(CPUx86 *cpu);
void x86_1D_SBB_D(CPUx86 *cpu);
void x86_1D_SBB_W(CPUx86 *cpu);

void x86_20_AND_B(CPUx86 *cpu);
void x86_21_AND_D(CPUx86 *cpu);
void x86_21_AND_W(CPUx86 *cpu);
void x86_22_AND_B(CPUx86 *cpu);
void x86_23_AND_D(CPUx86 *cpu);
void x86_23_AND_W(CPUx86 *cpu);
void x86_24_AND_B(CPUx86 *cpu);
void x86_25_AND_D(CPUx86 *cpu);
void x86_25_AND_W(CPUx86 *cpu);
void x86_28_SUB_B(CPUx86 *cpu);
void x86_29_SUB_D(CPUx86 *cpu);
void x86_29_SUB_W(CPUx86 *cpu);
void x86_2A_SUB_B(CPUx86 *cpu);
void x86_2B_SUB_D(CPUx86 *cpu);
void x86_2B_SUB_W(CPUx86 *cpu);
void x86_2C_SUB_B(CPUx86 *cpu);
void x86_2D_SUB_D(CPUx86 *cpu);
void x86_2D_SUB_W(CPUx86 *cpu);

void x86_30_XOR_B(CPUx86 *cpu);
void x86_31_XOR_D(CPUx86 *cpu);
void x86_31_XOR_W(CPUx86 *cpu);
void x86_32_XOR_B(CPUx86 *cpu);
void x86_33_XOR_D(CPUx86 *cpu);
void x86_33_XOR_W(CPUx86 *cpu);
void x86_34_XOR_B(CPUx86 *cpu);
void x86_35_XOR_D(CPUx86 *cpu);
void x86_35_XOR_W(CPUx86 *cpu);
void x86_38_CMP_B(CPUx86 *cpu);
void x86_39_CMP_D(CPUx86 *cpu);
void x86_39_CMP_W(CPUx86 *cpu);
void x86_3A_CMP_B(CPUx86 *cpu);
void x86_3B_CMP_D(CPUx86 *cpu);
void x86_3B_CMP_W(CPUx86 *cpu);
void x86_3C_CMP_B(CPUx86 *cpu);
void x86_3D_CMP_D(CPUx86 *cpu);
void x86_3D_CMP_W(CPUx86 *cpu);

void x86_40_INC_D(CPUx86 *cpu);
void x86_40_INC_W(CPUx86 *cpu);
void x86_48_DEC_D(CPUx86 *cpu);
void x86_48_DEC_W(CPUx86 *cpu);

void x86_70_JMPCC_REL8(CPUx86 *cpu);

void x86_80_ADD_B(CPUx86 *cpu);
void x86_81_ADD_W(CPUx86 *cpu);
void x86_81_ADD_D(CPUx86 *cpu);
void x86_83_ADD_W(CPUx86 *cpu);
void x86_83_ADD_D(CPUx86 *cpu);
void x86_80_OR_B(CPUx86 *cpu);
void x86_81_OR_W(CPUx86 *cpu);
void x86_81_OR_D(CPUx86 *cpu);
void x86_83_OR_W(CPUx86 *cpu);
void x86_83_OR_D(CPUx86 *cpu);
void x86_80_ADC_B(CPUx86 *cpu);
void x86_81_ADC_W(CPUx86 *cpu);
void x86_81_ADC_D(CPUx86 *cpu);
void x86_83_ADC_W(CPUx86 *cpu);
void x86_83_ADC_D(CPUx86 *cpu);
void x86_80_SBB_B(CPUx86 *cpu);
void x86_81_SBB_W(CPUx86 *cpu);
void x86_81_SBB_D(CPUx86 *cpu);
void x86_83_SBB_W(CPUx86 *cpu);
void x86_83_SBB_D(CPUx86 *cpu);
void x86_80_AND_B(CPUx86 *cpu);
void x86_81_AND_W(CPUx86 *cpu);
void x86_81_AND_D(CPUx86 *cpu);
void x86_83_AND_W(CPUx86 *cpu);
void x86_83_AND_D(CPUx86 *cpu);
void x86_80_SUB_B(CPUx86 *cpu);
void x86_81_SUB_W(CPUx86 *cpu);
void x86_81_SUB_D(CPUx86 *cpu);
void x86_83_SUB_W(CPUx86 *cpu);
void x86_83_SUB_D(CPUx86 *cpu);
void x86_80_XOR_B(CPUx86 *cpu);
void x86_81_XOR_W(CPUx86 *cpu);
void x86_81_XOR_D(CPUx86 *cpu);
void x86_83_XOR_W(CPUx86 *cpu);
void x86_83_XOR_D(CPUx86 *cpu);
void x86_80_CMP_B(CPUx86 *cpu);
void x86_81_CMP_W(CPUx86 *cpu);
void x86_81_CMP_D(CPUx86 *cpu);
void x86_83_CMP_W(CPUx86 *cpu);
void x86_83_CMP_D(CPUx86 *cpu);

void x86_84_TEST_B(CPUx86 *cpu);
void x86_85_TEST_W(CPUx86 *cpu);
void x86_85_TEST_D(CPUx86 *cpu);
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

void x86_A8_TEST_B(CPUx86 *cpu);
void x86_A9_TEST_W(CPUx86 *cpu);
void x86_A9_TEST_D(CPUx86 *cpu);

void x86_B0_MOV_B(CPUx86 *cpu);
void x86_B8_MOV_W(CPUx86 *cpu);
void x86_B8_MOV_D(CPUx86 *cpu);

void x86_C6_MOV_B(CPUx86 *cpu);
void x86_C7_MOV_W(CPUx86 *cpu);
void x86_C7_MOV_D(CPUx86 *cpu);

void x86_E9_NEAR_JMP_REL16(CPUx86 *cpu);
void x86_E9_NEAR_JMP_REL32(CPUx86 *cpu);
void x86_EB_SHORT_JMP_REL8(CPUx86 *cpu);

void x86_F6_TEST_B(CPUx86 *cpu);
void x86_F7_TEST_W(CPUx86 *cpu);
void x86_F7_TEST_D(CPUx86 *cpu);
void x86_FE_INC_B(CPUx86 *cpu);
void x86_FE_DEC_B(CPUx86 *cpu);
void x86_FF_INC_W(CPUx86 *cpu);
void x86_FF_INC_D(CPUx86 *cpu);
void x86_FF_DEC_W(CPUx86 *cpu);
void x86_FF_DEC_D(CPUx86 *cpu);
void x86_FF_NEAR_JMP_D(CPUx86 *cpu);
void x86_FF_NEAR_JMP_W(CPUx86 *cpu);

