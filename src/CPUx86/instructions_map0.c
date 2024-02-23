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

#include "instructions_map0.h"

uint32_t PARITY_TAB[8] = {
  0x69969669,
  0x96696996,
  0x96696996,
  0x69969669,
  0x96696996,
  0x69969669,
  0x69969669,
  0x96696996
};

void call_instruction_map0(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  bool arg_size = decoder->arg_size == DWORD; 
  printf("CALL: %x %i\n", decoder->opcode, arg_size);

  switch (decoder->opcode) {
    case 0x00: x86_00_ADD_B(cpu); break;
    case 0x01: arg_size ? x86_01_ADD_D(cpu) : x86_01_ADD_W(cpu); break;
    case 0x02: x86_02_ADD_B(cpu); break;
    case 0x03: arg_size ? x86_03_ADD_D(cpu) : x86_03_ADD_W(cpu); break;
    case 0x04: x86_04_ADD_B(cpu); break;
    case 0x05: arg_size ? x86_05_ADD_D(cpu) : x86_05_ADD_W(cpu); break;
    case 0x08: x86_08_OR_B(cpu); break;
    case 0x09: arg_size ? x86_09_OR_D(cpu) : x86_09_OR_W(cpu); break;
    case 0x0a: x86_0A_OR_B(cpu); break;
    case 0x0b: arg_size ? x86_0B_OR_D(cpu) : x86_0B_OR_W(cpu); break;
    case 0x0c: x86_0C_OR_B(cpu); break;
    case 0x0d: arg_size ? x86_0D_OR_D(cpu) : x86_0D_OR_W(cpu); break;

    case 0x10: x86_10_ADC_B(cpu); break;
    case 0x11: arg_size ? x86_11_ADC_D(cpu) : x86_11_ADC_W(cpu); break;
    case 0x12: x86_12_ADC_B(cpu); break;
    case 0x13: arg_size ? x86_13_ADC_D(cpu) : x86_13_ADC_W(cpu); break;
    case 0x14: x86_14_ADC_B(cpu); break;
    case 0x15: arg_size ? x86_15_ADC_D(cpu) : x86_15_ADC_W(cpu); break;
    case 0x18: x86_18_SBB_B(cpu); break;
    case 0x19: arg_size ? x86_19_SBB_D(cpu) : x86_19_SBB_W(cpu); break;
    case 0x1a: x86_1A_SBB_B(cpu); break;
    case 0x1b: arg_size ? x86_1B_SBB_D(cpu) : x86_1B_SBB_W(cpu); break;
    case 0x1c: x86_1C_SBB_B(cpu); break;
    case 0x1d: arg_size ? x86_1D_SBB_D(cpu) : x86_1D_SBB_W(cpu); break;

    case 0x20: x86_20_AND_B(cpu); break;
    case 0x21: arg_size ? x86_21_AND_D(cpu) : x86_21_AND_W(cpu); break;
    case 0x22: x86_22_AND_B(cpu); break;
    case 0x23: arg_size ? x86_23_AND_D(cpu) : x86_23_AND_W(cpu); break;
    case 0x24: x86_24_AND_B(cpu); break;
    case 0x25: arg_size ? x86_25_AND_D(cpu) : x86_25_AND_W(cpu); break;
    case 0x28: x86_28_SUB_B(cpu); break;
    case 0x29: arg_size ? x86_29_SUB_D(cpu) : x86_29_SUB_W(cpu); break;
    case 0x2a: x86_2A_SUB_B(cpu); break;
    case 0x2b: arg_size ? x86_2B_SUB_D(cpu) : x86_2B_SUB_W(cpu); break;
    case 0x2c: x86_2C_SUB_B(cpu); break;
    case 0x2d: arg_size ? x86_2D_SUB_D(cpu) : x86_2D_SUB_W(cpu); break;

    case 0x30: x86_30_XOR_B(cpu); break;
    case 0x31: arg_size ? x86_31_XOR_D(cpu) : x86_31_XOR_W(cpu); break;
    case 0x32: x86_32_XOR_B(cpu); break;
    case 0x33: arg_size ? x86_33_XOR_D(cpu) : x86_33_XOR_W(cpu); break;
    case 0x34: x86_34_XOR_B(cpu); break;
    case 0x35: arg_size ? x86_35_XOR_D(cpu) : x86_35_XOR_W(cpu); break;
    case 0x38: x86_38_CMP_B(cpu); break;
    case 0x39: arg_size ? x86_39_CMP_D(cpu) : x86_39_CMP_W(cpu); break;
    case 0x3a: x86_3A_CMP_B(cpu); break;
    case 0x3b: arg_size ? x86_3B_CMP_D(cpu) : x86_3B_CMP_W(cpu); break;
    case 0x3c: x86_3C_CMP_B(cpu); break;
    case 0x3d: arg_size ? x86_3D_CMP_D(cpu) : x86_3D_CMP_W(cpu); break;

    case 0x40: arg_size ? x86_40_INC_D(cpu) : x86_40_INC_W(cpu); break;
    case 0x48: arg_size ? x86_48_DEC_D(cpu) : x86_48_DEC_W(cpu); break;

    case 0x70: x86_70_JMPCC_REL8(cpu); break;

    case 0x82: /* opcode 0x82 is same as 0x80 */
    case 0x80: {
      switch (decoder->nnn) {
        case 0: x86_80_ADD_B(cpu); break;
        case 1: x86_80_OR_B(cpu); break;
        case 2: x86_80_ADC_B(cpu); break;
        case 3: x86_80_SBB_B(cpu); break;
        case 4: x86_80_AND_B(cpu); break;
        case 5: x86_80_SUB_B(cpu); break;
        case 6: x86_80_XOR_B(cpu); break;
        case 7: x86_80_CMP_B(cpu); break;
      }

      break;
    }
    case 0x81: {
      switch (decoder->nnn) {
        case 0: arg_size ? x86_81_ADD_D(cpu) : x86_81_ADD_W(cpu); break;
        case 1: arg_size ? x86_81_OR_D(cpu) : x86_81_OR_W(cpu); break;
        case 2: arg_size ? x86_81_ADC_D(cpu) : x86_81_ADC_W(cpu); break;
        case 3: arg_size ? x86_81_SBB_D(cpu) : x86_81_SBB_W(cpu); break;
        case 4: arg_size ? x86_81_AND_D(cpu) : x86_81_AND_W(cpu); break;
        case 5: arg_size ? x86_81_SUB_D(cpu) : x86_81_SUB_W(cpu); break;
        case 6: arg_size ? x86_81_XOR_D(cpu) : x86_81_XOR_W(cpu); break;
        case 7: arg_size ? x86_81_CMP_D(cpu) : x86_81_CMP_W(cpu); break;
      }

      break;
    }
    case 0x83: {
      switch (decoder->nnn) {
        case 0: arg_size ? x86_83_ADD_D(cpu) : x86_83_ADD_W(cpu); break;
        case 1: arg_size ? x86_83_OR_D(cpu) : x86_83_OR_W(cpu); break;
        case 2: arg_size ? x86_83_ADC_D(cpu) : x86_83_ADC_W(cpu); break;
        case 3: arg_size ? x86_83_SBB_D(cpu) : x86_83_SBB_W(cpu); break;
        case 4: arg_size ? x86_83_AND_D(cpu) : x86_83_AND_W(cpu); break;
        case 5: arg_size ? x86_83_SUB_D(cpu) : x86_83_SUB_W(cpu); break;
        case 6: arg_size ? x86_83_XOR_D(cpu) : x86_83_XOR_W(cpu); break;
        case 7: arg_size ? x86_83_CMP_D(cpu) : x86_83_CMP_W(cpu); break;
      }

      break;
    }

    case 0x84: x86_84_TEST_B(cpu); break;
    case 0x85: arg_size ? x86_85_TEST_W(cpu) : x86_85_TEST_D(cpu); break;
    case 0x86: x86_86_XCHG_B(cpu); break;
    case 0x87: arg_size ? x86_87_XCHG_D(cpu) : x86_87_XCHG_W(cpu); break;
    case 0x88: x86_88_MOV_B(cpu); break;
    case 0x89: arg_size ? x86_89_MOV_D(cpu) : x86_89_MOV_W(cpu); break;
    case 0x8a: x86_8A_MOV_B(cpu); break;
    case 0x8b: arg_size ? x86_8B_MOV_D(cpu) : x86_8B_MOV_W(cpu); break;

    case 0x90: arg_size ? x86_90_XCHG_D(cpu) : x86_90_XCHG_W(cpu); break;

    case 0xa8: x86_A8_TEST_B(cpu); break;
    case 0xa9: arg_size ? x86_A9_TEST_W(cpu) : x86_A9_TEST_D(cpu); break;

    case 0xb0: x86_B0_MOV_B(cpu); break;
    case 0xb8: arg_size ? x86_B8_MOV_D(cpu) : x86_B8_MOV_W(cpu); break;

    case 0xc6: x86_C6_MOV_B(cpu); break;
    case 0xc7: arg_size ? x86_C7_MOV_D(cpu) : x86_C7_MOV_W(cpu); break;

    case 0xe9: arg_size ? x86_E9_NEAR_JMP_REL32(cpu) : x86_E9_NEAR_JMP_REL16(cpu); break;
    case 0xeb: x86_EB_SHORT_JMP_REL8(cpu); break;

    case 0xf6: {
      switch (decoder->nnn) {
        case 0: x86_F6_TEST_B(cpu); break;
      }

      break;
    }
    case 0xf7: {
      switch (decoder->nnn) {
        case 0: arg_size ? x86_F7_TEST_D(cpu) : x86_F7_TEST_W(cpu); break;
      }

      break;
    } 
    case 0xfe: {
      switch (decoder->nnn) {
        case 0: x86_FE_INC_B(cpu); break;
        case 1: x86_FE_DEC_B(cpu); break;
      }

      break;
    }
    case 0xff: {
      switch (decoder->nnn) {
        case 0: arg_size ? x86_FF_INC_D(cpu) : x86_FF_INC_W(cpu); break;
        case 1: arg_size ? x86_FF_DEC_D(cpu) : x86_FF_DEC_W(cpu); break;
        case 4: arg_size ? x86_FF_NEAR_JMP_D(cpu) : x86_FF_NEAR_JMP_W(cpu); break;
      }

      break;
    }








  }

  return;
}











// =============================================================================
//   flags generators 
// =============================================================================

uint32_t generate_flags_add_byte(uint16_t src1, uint16_t src2, uint16_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x100, EFLAGS_CARRY_FLAG);
  res_flags |= CONDITIONAL_FLAG(res & 0x80, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint16_t carry_chain = CARRY_CHAIN(src1, src2, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(carry_chain >> 6), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(carry_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_add_word(uint32_t src1, uint32_t src2, uint32_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x10000, EFLAGS_CARRY_FLAG);
  res_flags |= CONDITIONAL_FLAG(res & 0x8000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint32_t carry_chain = CARRY_CHAIN(src1, src2, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(carry_chain >> 14), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(carry_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_add_dword(uint64_t src1, uint64_t src2, uint64_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x100000000, EFLAGS_CARRY_FLAG);
  res_flags |= CONDITIONAL_FLAG(res & 0x80000000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffffffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint64_t carry_chain = CARRY_CHAIN(src1, src2, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(carry_chain >> 30), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(carry_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_sub_byte(uint16_t src1, uint16_t src2, uint16_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint16_t borrow_chain = BORROW_CHAIN(src1, src2, res);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x80, EFLAGS_CARRY_FLAG);
  res_flags |= CONDITIONAL_FLAG(XOR2(borrow_chain >> 6), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_sub_word(uint32_t src1, uint32_t src2, uint32_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x8000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint32_t borrow_chain = BORROW_CHAIN(src1, src2, res);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x8000, EFLAGS_CARRY_FLAG);
  res_flags |= CONDITIONAL_FLAG(XOR2(borrow_chain >> 14), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_sub_dword(uint64_t src1, uint64_t src2, uint64_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80000000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffffffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint64_t borrow_chain = BORROW_CHAIN(src1, src2, res);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x80000000, EFLAGS_CARRY_FLAG);
  res_flags |= CONDITIONAL_FLAG(XOR2(borrow_chain >> 30), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_bitlogic_byte(uint8_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG(res == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res), EFLAGS_PARITY_FLAG);

  return res_flags;
}

uint32_t generate_flags_bitlogic_word(uint16_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x8000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG(res == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res), EFLAGS_PARITY_FLAG);

  return res_flags;
}

uint32_t generate_flags_bitlogic_dword(uint32_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80000000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG(res == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res), EFLAGS_PARITY_FLAG);

  return res_flags;
}

uint32_t generate_flags_inc_byte(uint8_t src1, uint8_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint8_t carry_chain = CARRY_CHAIN(src1, 1, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(carry_chain >> 6), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(carry_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_inc_word(uint16_t src1, uint16_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x8000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint16_t carry_chain = CARRY_CHAIN(src1, 1, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(carry_chain >> 14), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(carry_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_inc_dword(uint32_t src1, uint32_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80000000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffffffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint32_t carry_chain = CARRY_CHAIN(src1, 1, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(carry_chain >> 30), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(carry_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_dec_byte(uint8_t src1, uint8_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint8_t borrow_chain = BORROW_CHAIN(src1, 1, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(borrow_chain >> 6), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_dec_word(uint16_t src1, uint16_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x8000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint16_t borrow_chain = BORROW_CHAIN(src1, 1, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(borrow_chain >> 14), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

uint32_t generate_flags_dec_dword(uint32_t src1, uint32_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80000000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res & 0xffffffff) == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res & 0xff), EFLAGS_PARITY_FLAG);
  uint32_t borrow_chain = BORROW_CHAIN(src1, 1, res);
  res_flags |= CONDITIONAL_FLAG(XOR2(borrow_chain >> 30), EFLAGS_OVERFLOW_FLAG);
  res_flags |= CONDITIONAL_FLAG(borrow_chain & 0x8, EFLAGS_ADJUST_FLAG);

  return res_flags;
}

// =============================================================================
//   00 - 0F opcodes
// =============================================================================

/* 00: ADD byte r/m, r8 */
void x86_00_ADD_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t res = src1 + src2;
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 01: ADD word r/m, r16 */
void x86_01_ADD_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t res = src1 + src2;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 01: ADD dword r/m, r32 */
void x86_01_ADD_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t res = src1 + src2;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 02: ADD r8, byte r/m */
void x86_02_ADD_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t src2 = load_rm(cpu, BYTE);
  uint16_t res = src1 + src2;
  store_gpr(cpu, decoder->nnn, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 03: ADD r16, word r/m */
void x86_03_ADD_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t src2 = load_rm(cpu, WORD);
  uint32_t res = src1 + src2;
  store_gpr(cpu, decoder->nnn, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 03: ADD r32, dword r/m */
void x86_03_ADD_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t src2 = load_rm(cpu, DWORD);
  uint64_t res = src1 + src2;
  store_gpr(cpu, decoder->nnn, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 04: ADD al, i8 */
void x86_04_ADD_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_gpr(cpu, AL, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 + src2;
  store_gpr(cpu, AL, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 05: ADD ax, i16 */
void x86_05_ADD_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_gpr(cpu, AX, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 + src2;
  store_gpr(cpu, AX, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 05: ADD eax, i32 */
void x86_05_ADD_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_gpr(cpu, EAX, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 + src2;
  store_gpr(cpu, EAX, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}


/* 08: OR byte r/m, r8 */
void x86_08_OR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t res = src1 | src2;
  store_rm(cpu, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 09: OR word r/m, r16 */
void x86_09_OR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t res = src1 | src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 09: OR dword r/m, r32 */
void x86_09_OR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t res = src1 | src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 0A: OR r8, byte r/m */
void x86_0A_OR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint8_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t src2 = load_rm(cpu, BYTE);
  uint8_t res = src1 | src2;
  store_gpr(cpu, decoder->nnn, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 0B: OR r16, word r/m */
void x86_0B_OR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t src2 = load_rm(cpu, WORD);
  uint16_t res = src1 | src2;
  store_gpr(cpu, decoder->nnn, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 0B: OR r32, dword r/m */
void x86_0B_OR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t src2 = load_rm(cpu, DWORD);
  uint32_t res = src1 | src2;
  store_gpr(cpu, decoder->nnn, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 0C: OR al, i8 */
void x86_0C_OR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_gpr(cpu, AL, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 | src2;
  store_gpr(cpu, AL, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 0D: OR ax, i16 */
void x86_0D_OR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_gpr(cpu, AX, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 | src2;
  store_gpr(cpu, AX, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 0D: OR eax, i32 */
void x86_0D_OR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_gpr(cpu, EAX, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 | src2;
  store_gpr(cpu, EAX, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

// =============================================================================
//   10 - 1F opcodes
// =============================================================================

/* 10: ADC byte r/m, r8 */
void x86_10_ADC_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 + src2 + carry_in;
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}


 
/* 11: ADC word r/m, r16 */
void x86_11_ADC_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 + src2 + carry_in;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 11: ADC dword r/m, r32 */
void x86_11_ADC_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 + src2 + carry_in;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 12: ADC r8, byte r/m */
void x86_12_ADC_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t src2 = load_rm(cpu, BYTE);
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 + src2 + carry_in;
  store_gpr(cpu, decoder->nnn, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 13: ADC r16, word r/m */
void x86_13_ADC_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t src2 = load_rm(cpu, WORD);
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 + src2 + carry_in;
  store_gpr(cpu, decoder->nnn, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 13: ADC r32, dword r/m */
void x86_13_ADC_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t src2 = load_rm(cpu, DWORD);
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 + src2 + carry_in;
  store_gpr(cpu, decoder->nnn, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 14: ADC al, i8 */
void x86_14_ADC_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_gpr(cpu, AL, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 + src2 + carry_in;
  store_gpr(cpu, AL, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 15: ADC ax, i16 */
void x86_15_ADC_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_gpr(cpu, AX, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 + src2 + carry_in;
  store_gpr(cpu, AX, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 15: ADC eax, i32 */
void x86_15_ADC_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_gpr(cpu, EAX, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 + src2 + carry_in;
  store_gpr(cpu, EAX, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}


/* 18: SBB byte r/m, r8 */
void x86_18_SBB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 - (src2 + carry_in);
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 19: SBB word r/m, r16 */
void x86_19_SBB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 - (src2 + carry_in);
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 19: SBB dword r/m, r32 */
void x86_19_SBB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 - (src2 + carry_in);
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 1A: SBB r8, byte r/m */
void x86_1A_SBB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t src2 = load_rm(cpu, BYTE);
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 - (src2 + carry_in);
  store_gpr(cpu, decoder->nnn, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 1B: SBB r16, word r/m */
void x86_1B_SBB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t src2 = load_rm(cpu, WORD);
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 - (src2 + carry_in);
  store_gpr(cpu, decoder->nnn, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 1B: SBB r32, dword r/m */
void x86_1B_SBB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t src2 = load_rm(cpu, DWORD);
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 - (src2 + carry_in);
  store_gpr(cpu, decoder->nnn, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 1C: SBB al, i8 */
void x86_1C_SBB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_gpr(cpu, AL, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 - (src2 + carry_in);
  store_gpr(cpu, AL, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 1D: SBB ax, i16 */
void x86_1D_SBB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_gpr(cpu, AX, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 - (src2 + carry_in);
  store_gpr(cpu, AX, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 1D: SBB eax, i32 */
void x86_1D_SBB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_gpr(cpu, EAX, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 - (src2 + carry_in);
  store_gpr(cpu, EAX, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

// =============================================================================
//   20 - 2F opcodes
// =============================================================================

/* 20: AND byte r/m, r8 */
void x86_20_AND_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t res = src1 & src2;
  store_rm(cpu, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 21: AND word r/m, r16 */
void x86_21_AND_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t res = src1 & src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 21: AND dword r/m, r32 */
void x86_21_AND_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t res = src1 & src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 22: AND r8, byte r/m */
void x86_22_AND_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint8_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t src2 = load_rm(cpu, BYTE);
  uint8_t res = src1 & src2;
  store_gpr(cpu, decoder->nnn, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 23: AND r16, word r/m */
void x86_23_AND_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t src2 = load_rm(cpu, WORD);
  uint16_t res = src1 & src2;
  store_gpr(cpu, decoder->nnn, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 23: AND r32, dword r/m */
void x86_23_AND_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t src2 = load_rm(cpu, DWORD);
  uint32_t res = src1 & src2;
  store_gpr(cpu, decoder->nnn, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 24: AND al, i8 */
void x86_24_AND_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 & src2;
  store_gpr(cpu, AL, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 25: AND ax, i16 */
void x86_25_AND_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 & src2;
  store_gpr(cpu, AX, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 25: AND eax, i32 */
void x86_25_AND_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 & src2;
  store_gpr(cpu, EAX, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 28: SUB byte r/m, r8 */
void x86_28_SUB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t res = src1 - src2;
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 29: SUB word r/m, r16 */
void x86_29_SUB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t res = src1 - src2;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 29: SUB dword r/m, r32 */
void x86_29_SUB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t res = src1 - src2;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 2A: SUB r8, byte r/m */
void x86_2A_SUB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t src2 = load_rm(cpu, BYTE);
  uint16_t res = src1 - src2;
  store_gpr(cpu, decoder->nnn, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 2B: SUB r16, word r/m */
void x86_2B_SUB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t src2 = load_rm(cpu, WORD);
  uint32_t res = src1 - src2;
  store_gpr(cpu, decoder->nnn, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 2B: SUB r32, dword r/m */
void x86_2B_SUB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t src2 = load_rm(cpu, DWORD);
  uint64_t res = src1 - src2;
  store_gpr(cpu, decoder->nnn, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 2C: SUB al, i8 */
void x86_2C_SUB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_gpr(cpu, AL, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 - src2;
  store_gpr(cpu, AL, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 2D: SUB ax, i16 */
void x86_2D_SUB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_gpr(cpu, AX, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 - src2;
  store_gpr(cpu, AX, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 2D: SUB eax, i32 */
void x86_2D_SUB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_gpr(cpu, EAX, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 - src2;
  store_gpr(cpu, EAX, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

// =============================================================================
//   30 - 3F opcodes
// =============================================================================

/* 30: XOR byte r/m, r8 */
void x86_30_XOR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t res = src1 ^ src2;
  store_rm(cpu, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 31: XOR word r/m, r16 */
void x86_31_XOR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t res = src1 ^ src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 31: XOR dword r/m, r32 */
void x86_31_XOR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t res = src1 ^ src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 32: XOR r8, byte r/m */
void x86_32_XOR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint8_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t src2 = load_rm(cpu, BYTE);
  uint8_t res = src1 ^ src2;
  store_gpr(cpu, decoder->nnn, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 33: XOR r16, word r/m */
void x86_33_XOR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t src2 = load_rm(cpu, WORD);
  uint16_t res = src1 ^ src2;
  store_gpr(cpu, decoder->nnn, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 33: XOR r32, dword r/m */
void x86_33_XOR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t src2 = load_rm(cpu, DWORD);
  uint32_t res = src1 ^ src2;
  store_gpr(cpu, decoder->nnn, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 34: XOR al, i8 */
void x86_34_XOR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 ^ src2;
  store_gpr(cpu, AL, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 35: XOR ax, i16 */
void x86_35_XOR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 ^ src2;
  store_gpr(cpu, AX, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 35: XOR eax, i32 */
void x86_35_XOR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 ^ src2;
  store_gpr(cpu, EAX, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 38: CMP byte r/m, r8 */
void x86_38_CMP_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 39: CMP word r/m, r16 */
void x86_39_CMP_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 39: CMP dword r/m, r32 */
void x86_39_CMP_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 3A: CMP r8, byte r/m */
void x86_3A_CMP_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint16_t src2 = load_rm(cpu, BYTE);
  uint16_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 3B: CMP r16, word r/m */
void x86_3B_CMP_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint32_t src2 = load_rm(cpu, WORD);
  uint32_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 3B: CMP r32, dword r/m */
void x86_3B_CMP_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint64_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint64_t src2 = load_rm(cpu, DWORD);
  uint64_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 3C: CMP al, i8 */
void x86_3C_CMP_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_gpr(cpu, AL, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 3D: CMP ax, i16 */
void x86_3D_CMP_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_gpr(cpu, AX, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 3D: CMP eax, i32 */
void x86_3D_CMP_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_gpr(cpu, EAX, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

// =============================================================================
//   40 - 4F opcodes
// =============================================================================

/* 40-47: INC r16 */
void x86_40_INC_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;

  uint16_t src = load_gpr(cpu, decoder->opc_arg, WORD);
  uint16_t res = src + 1;
  store_gpr(cpu, decoder->opc_arg, WORD, res);

  uint32_t res_flags = generate_flags_inc_word(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 40-47: INC r32 */
void x86_40_INC_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;

  uint32_t src = load_gpr(cpu, decoder->opc_arg, DWORD);
  uint32_t res = src + 1;
  store_gpr(cpu, decoder->opc_arg, DWORD, res);

  uint32_t res_flags = generate_flags_inc_dword(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 48-4F: DEC r16 */
void x86_48_DEC_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;

  uint16_t src = load_gpr(cpu, decoder->opc_arg, WORD);
  uint16_t res = src - 1;
  store_gpr(cpu, decoder->opc_arg, WORD, res);

  uint32_t res_flags = generate_flags_dec_word(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 48-4F: DEC r32 */
void x86_48_DEC_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;

  uint32_t src = load_gpr(cpu, decoder->opc_arg, DWORD);
  uint32_t res = src - 1;
  store_gpr(cpu, decoder->opc_arg, DWORD, res);

  uint32_t res_flags = generate_flags_dec_dword(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

// =============================================================================
//   70 - 7F opcodes
// =============================================================================

/* EB: short JMP rel8 */
void x86_70_JMPCC_REL8(CPUx86 *cpu) {
    Decoder *decoder = cpu->decoder;
    decode_imm(cpu, BYTE);
    
    uint8_t cc = decoder->opc_arg;
    bool test_flag = check_eflags_with_cc(cpu, cc);
    if (test_flag) {
      uint32_t rel = (int32_t)(int8_t)(decoder->imm & 0xff);
      uint32_t eip = cpu->eip + (decoder->decode_flags & DECODER_BYTES_CNT);
      cpu->new_eip = eip + rel;
      cpu->new_eip_set = true;
    }

    return;
}

// =============================================================================
//   80 - 83 opcodes
// =============================================================================

/* 80 /0: ADD byte r/m, i8 */
void x86_80_ADD_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 + src2;
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 81 /0: ADD word r/m, i16 */
void x86_81_ADD_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 + src2;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /0: ADD dword r/m, i32 */
void x86_81_ADD_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 + src2;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /0: ADD word r/m, i8 */
void x86_83_ADD_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 + src2;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /0: ADD dword r/m, i8 */
void x86_83_ADD_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 + src2;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 80 /1: OR byte r/m, i8 */
void x86_80_OR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 | src2;
  store_rm(cpu, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /1: OR word r/m, i16 */ 
void x86_81_OR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 | src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /1: OR dword r/m, i32 */
void x86_81_OR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 | src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /1: OR word r/m, i8 */
void x86_83_OR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 | src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /1: OR dword r/m, i8 */
void x86_83_OR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 | src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 80 /2: ADC byte r/m, i8 */
void x86_80_ADC_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 + src2 + carry_in;
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_add_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /2: ADC word r/m, i16 */
void x86_81_ADC_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 + src2 + carry_in;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /2: ADC dword r/m, i32 */
void x86_81_ADC_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 + src2 + carry_in;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /2: ADC word r/m, i8 */
void x86_83_ADC_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 + src2 + carry_in;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_add_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /2: ADC dword r/m, i8 */
void x86_83_ADC_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 + src2 + carry_in;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_add_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 80 /3: SBB byte r/m, i8 */
void x86_80_SBB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint16_t res = src1 - (src2 + carry_in);
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 81 /3: SBB word r/m, i16 */
void x86_81_SBB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 - (src2 + carry_in);
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /3: SBB dword r/m, i32 */
void x86_81_SBB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 - (src2 + carry_in);
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /3: SBB word r/m, i8 */
void x86_83_SBB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint32_t res = src1 - (src2 + carry_in);
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /3: SBB dword r/m, i8 */
void x86_83_SBB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t carry_in = cpu->eflags & EFLAGS_CARRY_FLAG;
  uint64_t res = src1 - (src2 + carry_in);
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 80 /4: AND byte r/m, i8 */
void x86_80_AND_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 & src2;
  store_rm(cpu, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /4: AND word r/m, i16 */
void x86_81_AND_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 & src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /4: AND dword r/m, i32 */
void x86_81_AND_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 & src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /4: AND word r/m, i8 */
void x86_83_AND_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 & src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /4: AND dword r/m, i8 */
void x86_83_AND_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 & src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}


/* 80 /5: SUB byte r/m, i8 */
void x86_80_SUB_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 - src2;
  store_rm(cpu, BYTE, (uint8_t)(res & 0xff));
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 81 /5: SUB word r/m, i16 */
void x86_81_SUB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 - src2;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /5: SUB dword r/m, i32 */
void x86_81_SUB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 - src2;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /5: SUB word r/m, i8 */
void x86_83_SUB_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 - src2;
  store_rm(cpu, WORD, (uint16_t)(res & 0xffff));
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /5: SUB dword r/m, i8 */
void x86_83_SUB_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 - src2;
  store_rm(cpu, DWORD, (uint32_t)(res & 0xffffffff));
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}


/* 80 /6: XOR byte r/m, i8 */
void x86_80_XOR_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 ^ src2;
  store_rm(cpu, BYTE, res);
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 81 /6: XOR word r/m, i16 */
void x86_81_XOR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 ^ src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /6: XOR dword r/m, i32 */
void x86_81_XOR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 ^ src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /6: XOR word r/m, i8 */
void x86_83_XOR_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 ^ src2;
  store_rm(cpu, WORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /6: XOR dword r/m, i8 */
void x86_83_XOR_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 ^ src2;
  store_rm(cpu, DWORD, res);
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 80 /7: CMP byte r/m, i8 */
void x86_80_CMP_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint16_t src1 = load_rm(cpu, BYTE);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_byte(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 81 /7: CMP word r/m, i16 */
void x86_81_CMP_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 81 /7: CMP dword r/m, i32 */
void x86_81_CMP_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /7: CMP word r/m, i8 */
void x86_83_CMP_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint32_t src1 = load_rm(cpu, WORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_word(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 83 /7: CMP dword r/m, i8 */
void x86_83_CMP_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint64_t src1 = load_rm(cpu, DWORD);
  uint64_t src2 = decoder->imm;
  uint64_t res = src1 - src2;
  
  uint32_t res_flags = generate_flags_sub_dword(src1, src2, res); 
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

// =============================================================================
//   84 - 8F opcodes
// =============================================================================

/* 84: TEST byte r/m, r8 */
void x86_84_TEST_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* 85: TEST word r/m, r16 */
void x86_85_TEST_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 85: TEST dword r/m, r32 */
void x86_85_TEST_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* 86: XCHG byte r/m, r8 */
void x86_86_XCHG_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = load_gpr(cpu, decoder->nnn, BYTE);
  store_rm(cpu, BYTE, src2);
  store_gpr(cpu, decoder->nnn, BYTE, src1);

  return;
} 

/* 87: XCHG word r/m, r16 */
void x86_87_XCHG_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = load_gpr(cpu, decoder->nnn, WORD);
  store_rm(cpu, WORD, src2);
  store_gpr(cpu, decoder->nnn, WORD, src1);

  return;
} 

/* 87: XCHG dword r/m, r32 */
void x86_87_XCHG_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = load_gpr(cpu, decoder->nnn, DWORD);
  store_rm(cpu, DWORD, src2);
  store_gpr(cpu, decoder->nnn, DWORD, src1);

  return;
} 

/* 88: MOV byte r/m, r8 */
void x86_88_MOV_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint8_t src = load_gpr(cpu, decoder->nnn, BYTE);
  store_rm(cpu, BYTE, src);
  
  return;  
}

/* 89: MOV word r/m, r16 */
void x86_89_MOV_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint16_t src = load_gpr(cpu, decoder->nnn, WORD);
  store_rm(cpu, WORD, src);
  
  return;  
}

/* 89: MOV dword r/m, r32 */
void x86_89_MOV_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint8_t src = load_gpr(cpu, decoder->nnn, DWORD);
  store_rm(cpu, DWORD, src);
  
  return;  
}

/* 8A: MOV r8, byte r/m */
void x86_8A_MOV_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint8_t src = load_rm(cpu, BYTE);
  store_gpr(cpu, decoder->nnn, BYTE, src);
  
  return;  
}

/* 8B: MOV r16, word r/m */
void x86_8B_MOV_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);

  uint16_t src = load_rm(cpu, WORD);
  store_gpr(cpu, decoder->nnn, WORD, src);
  
  return;  
}

/* 8B: MOV r32, dword r/m */
void x86_8B_MOV_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_modrm(cpu);
 
  uint32_t src = load_rm(cpu, DWORD);
  store_gpr(cpu, decoder->nnn, DWORD, src);
  
  return;  
}

// =============================================================================
//   90 - 9F opcodes
// =============================================================================

/* 90-97: XCHG ax, r16 */
void x86_90_XCHG_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;

  uint16_t src1 = load_gpr(cpu, AX, WORD);
  uint16_t src2 = load_gpr(cpu, decoder->opc_arg, WORD);
  store_gpr(cpu, AX, WORD, src2);
  store_gpr(cpu, decoder->opc_arg, WORD, src1);

  return;
}

/* 90-97: XCHG ax, r32 */
void x86_90_XCHG_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;

  uint32_t src1 = load_gpr(cpu, EAX, DWORD);
  uint32_t src2 = load_gpr(cpu, decoder->opc_arg, DWORD);

  store_gpr(cpu, EAX, DWORD, src2);
  store_gpr(cpu, decoder->opc_arg, DWORD, src1);

  return;
}

// =============================================================================
//   A0 - AF opcodes
// =============================================================================

/* A8: TEST al, i8 */
void x86_A8_TEST_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_gpr(cpu, decoder->nnn, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}
 
/* A9: TEST ax, i16 */
void x86_A9_TEST_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_gpr(cpu, decoder->nnn, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* A9: TEST eax, i32 */
void x86_A9_TEST_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_gpr(cpu, decoder->nnn, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

// =============================================================================
//   B0 - BF opcodes
// =============================================================================

/* B0-B7: MOV r8, i8 */
void x86_B0_MOV_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE);
  
  uint8_t imm = decoder->imm;   
  store_gpr(cpu, decoder->opc_arg, BYTE, imm);
  
  return;
}

/* B8-BF: MOV r16, i16 */
void x86_B8_MOV_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD);
  
  uint16_t imm = decoder->imm;   
  store_gpr(cpu, decoder->opc_arg, WORD, imm);
  
  return;  
}

/* B8-BF: MOV r32, i32 */
void x86_B8_MOV_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD);
  
  uint32_t imm = decoder->imm;   
  printf("B8: MOV %i, %x\n", decoder->opc_arg, imm);
  store_gpr(cpu, decoder->opc_arg, DWORD, imm);
  
  return;  
}

// =============================================================================
//   C0 - CF opcodes
// =============================================================================

/* C6: MOV byte r/m, i8 */
void x86_C6_MOV_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE);
  
  uint8_t imm = decoder->imm;   
  store_rm(cpu, BYTE, imm);
  
  return;
}

/* C7: MOV word r/m, i16 */
void x86_C7_MOV_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD);
  
  uint16_t imm = decoder->imm;   
  store_rm(cpu, WORD, imm);
  
  return;
}

/* C7: MOV dword r/m, i32 */
void x86_C7_MOV_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD);
  
  uint8_t imm = decoder->imm;   
  store_rm(cpu, DWORD, imm);
  
  return;
}

// =============================================================================
//   E0 - EF opcodes
// =============================================================================

/* E9: near JMP rel16 */
void x86_E9_NEAR_JMP_REL16(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD);

  uint16_t rel = (int32_t)(int16_t)(decoder->imm & 0xffff);;
  uint32_t eip = cpu->eip + (decoder->decode_flags & DECODER_BYTES_CNT);
  cpu->new_eip = (eip + rel) & 0x0000ffff;
  cpu->new_eip_set = true;

  return;
} 

/* E9: near JMP rel32 */
void x86_E9_NEAR_JMP_REL32(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD);

  uint32_t rel = decoder->imm;
  uint32_t eip = cpu->eip + (decoder->decode_flags & DECODER_BYTES_CNT);
  cpu->new_eip = eip + rel;
  cpu->new_eip_set = true;

  return;
}

/* EB: short JMP rel8 */
void x86_EB_SHORT_JMP_REL8(CPUx86 *cpu) {
    Decoder *decoder = cpu->decoder;
    decode_imm(cpu, BYTE);
    
    uint32_t rel = (int32_t)(int8_t)(decoder->imm & 0xff);
    uint32_t eip = cpu->eip + (decoder->decode_flags & DECODER_BYTES_CNT);
    cpu->new_eip = eip + rel;
    cpu->new_eip_set = true;
    
    return;
}

// =============================================================================
//   F0 - FF opcodes
// =============================================================================

/* F6 /0: TEST byte r/m, i8 */
void x86_F6_TEST_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE); 

  uint8_t src1 = load_rm(cpu, BYTE);
  uint8_t src2 = decoder->imm;
  uint8_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_byte(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* F7 /0: TEST word r/m, i16 */
void x86_F7_TEST_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD); 

  uint16_t src1 = load_rm(cpu, WORD);
  uint16_t src2 = decoder->imm;
  uint16_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_word(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* F7 /0: TEST dword r/m, i32 */
void x86_F7_TEST_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD); 

  uint32_t src1 = load_rm(cpu, DWORD);
  uint32_t src2 = decoder->imm;
  uint32_t res = src1 & src2;
  
  uint32_t res_flags = generate_flags_bitlogic_dword(res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}


/* FE /0: INC byte r/m */
void x86_FE_INC_B(CPUx86 *cpu) {
  uint8_t src = load_rm(cpu, BYTE);
  uint8_t res = src + 1;
  store_rm(cpu, BYTE, res);

  uint32_t res_flags = generate_flags_inc_byte(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* FE /1: DEC byte r/m */
void x86_FE_DEC_B(CPUx86 *cpu) {
  uint8_t src = load_rm(cpu, BYTE);
  uint8_t res = src - 1;
  store_rm(cpu, BYTE, res);

  uint32_t res_flags = generate_flags_dec_byte(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* FF /0: INC word r/m */
void x86_FF_INC_W(CPUx86 *cpu) {
  uint16_t src = load_rm(cpu, WORD);
  uint16_t res = src + 1;
  store_rm(cpu, WORD, res);

  uint32_t res_flags = generate_flags_inc_word(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* FF /0: INC dword r/m */
void x86_FF_INC_D(CPUx86 *cpu) {
  uint32_t src = load_rm(cpu, DWORD);
  uint32_t res = src + 1;
  store_rm(cpu, DWORD, res);

  uint32_t res_flags = generate_flags_inc_dword(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* FF /1: DEC word r/m */
void x86_FF_DEC_W(CPUx86 *cpu) {
  uint16_t src = load_rm(cpu, WORD);
  uint16_t res = src - 1;
  store_rm(cpu, WORD, res);

  uint32_t res_flags = generate_flags_dec_word(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* FF /1: DEC dword r/m */
void x86_FF_DEC_D(CPUx86 *cpu) {
  uint32_t src = load_rm(cpu, DWORD);
  uint32_t res = src - 1;
  store_rm(cpu, DWORD, res);

  uint32_t res_flags = generate_flags_dec_dword(src, res);
  UPDATE_EFLAGS(res_flags, EFLAGS_STATUS_FLAGS);

  return;
}

/* FF /4: near JMP word r/m */
void x86_FF_NEAR_JMP_W(CPUx86 *cpu) {
  uint32_t src = load_rm(cpu, WORD);
  cpu->new_eip = src;
  cpu->new_eip_set = true;

  return;
}

/* FF /4: near JMP dword r/m */
void x86_FF_NEAR_JMP_D(CPUx86 *cpu) {
  uint32_t src = load_rm(cpu, DWORD);
  cpu->new_eip = src;
  cpu->new_eip_set = true;
  return;
}



