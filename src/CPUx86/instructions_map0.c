#include "instructions_map0.h"

void call_instruction_map0(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  bool arg_size = decoder->arg_size == DWORD; 
  printf("CALL: %x %i", decoder->opcode, arg_size);

  switch (decoder->opcode) {
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