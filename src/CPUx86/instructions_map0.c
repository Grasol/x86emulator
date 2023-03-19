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
  /*0x69969660,
0x96696991,
0x96696992,
0x69969663,
0x96696994,
0x69969665,
0x69969666,
0x96696997*/
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

    case 0x10: x86_10_ADC_B(cpu); break;
    case 0x11: arg_size ? x86_11_ADC_D(cpu) : x86_11_ADC_W(cpu); break;
    case 0x12: x86_12_ADC_B(cpu); break;
    case 0x13: arg_size ? x86_13_ADC_D(cpu) : x86_13_ADC_W(cpu); break;
    case 0x14: x86_14_ADC_B(cpu); break;
    case 0x15: arg_size ? x86_15_ADC_D(cpu) : x86_15_ADC_W(cpu); break;

    case 0x86: x86_86_XCHG_B(cpu); break;
    case 0x87: arg_size ? x86_87_XCHG_D(cpu) : x86_87_XCHG_W(cpu); break;
    case 0x88: x86_88_MOV_B(cpu); break;
    case 0x89: arg_size ? x86_89_MOV_D(cpu) : x86_89_MOV_W(cpu); break;
    case 0x8a: x86_8A_MOV_B(cpu); break;
    case 0x8b: arg_size ? x86_8B_MOV_D(cpu) : x86_8B_MOV_W(cpu); break;

    case 0x90: arg_size ? x86_90_XCHG_D(cpu) : x86_90_XCHG_W(cpu); break;

    case 0xb0: x86_B0_MOV_B(cpu); break;
    case 0xb8: arg_size ? x86_B8_MOV_D(cpu) : x86_B8_MOV_W(cpu); break;

    case 0xe9: arg_size ? x86_E9_NEAR_JMP_REL32(cpu) : x86_E9_NEAR_JMP_REL16(cpu); break;
    case 0xeb: x86_EB_SHORT_JMP_REL8(cpu); break;
  }

  return;
}


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

uint32_t generate_flags_bitlogic_byte(uint8_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res), EFLAGS_PARITY_FLAG);

  return res_flags;
}

uint32_t generate_flags_bitlogic_word(uint16_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x8000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res), EFLAGS_PARITY_FLAG);

  return res_flags;
}

uint32_t generate_flags_bitlogic_dword(uint32_t res) {
  uint32_t res_flags = 0;

  res_flags |= CONDITIONAL_FLAG(res & 0x80000000, EFLAGS_SIGN_FLAG);
  res_flags |= CONDITIONAL_FLAG((res == 0, EFLAGS_ZERO_FLAG);
  res_flags |= CONDITIONAL_FLAG(PARITY(res), EFLAGS_PARITY_FLAG);

  return res_flags;
}



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
void x86_38_OR_B(CPUx86 *cpu) {
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
void x86_39_OR_W(CPUx86 *cpu) {
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
void x86_39_OR_D(CPUx86 *cpu) {
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
void x86_3A_OR_B(CPUx86 *cpu) {
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
void x86_3B_OR_W(CPUx86 *cpu) {
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
void x86_3B_OR_D(CPUx86 *cpu) {
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
void x86_3C_OR_B(CPUx86 *cpu) {
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
void x86_3D_OR_W(CPUx86 *cpu) {
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
void x86_3D_OR_D(CPUx86 *cpu) {
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

/* B0-B7: MOV byte r8, i8 */
void x86_B0_MOV_B(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, BYTE);
  
  uint8_t imm = decoder->imm;   
  store_gpr(cpu, decoder->opc_arg, BYTE, imm);
  
  return;
}

/* B8-BF: MOV word r16, i16 */
void x86_B8_MOV_W(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, WORD);
  
  uint16_t imm = decoder->imm;   
  store_gpr(cpu, decoder->opc_arg, WORD, imm);
  
  return;  
}

/* B8-BF: MOV byte r32, i32 */
void x86_B8_MOV_D(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  decode_imm(cpu, DWORD);
  
  uint32_t imm = decoder->imm;   
  printf("B8 MOV: %x\n", imm);
  store_gpr(cpu, decoder->opc_arg, DWORD, imm);
  
  return;  
}

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