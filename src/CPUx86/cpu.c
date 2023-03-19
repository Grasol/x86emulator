#include "cpu.h"
#include "instructions_map0.h"
#include "segmentation.h"
#include "paging.h"

CPUx86 *new_CPUx86() {
  CPUx86 *cpu = malloc(sizeof(CPUx86));
  if (!cpu) {
    goto memory_error;
  }

  cpu->gpr = malloc(sizeof(uint32_t) * 8);
  if (!cpu->gpr) {
    goto memory_error;
  }
  // TODO: exit(1)

  cpu->seg = malloc(sizeof(SegmentReg) * 6);
  cpu->gdtr = malloc(sizeof(SegmentReg));
  cpu->ldtr = malloc(sizeof(SegmentReg));
  cpu->idtr = malloc(sizeof(SegmentReg));
  cpu->tr = malloc(sizeof(SegmentReg));
  
  cpu->creg = malloc(sizeof(uint32_t) * 8);
  cpu->dreg = malloc(sizeof(uint32_t) * 8);
  
  cpu->freg = malloc(sizeof(FPUReg) * 8);
  cpu->xmm = malloc(sizeof(SSEReg) * 8);
  cpu->ilist = ILIST_init();
  cpu->decoder = malloc(sizeof(Decoder));

  if (!(cpu->seg || cpu->gdtr || cpu->ldtr || cpu->idtr || cpu->tr || cpu->creg || 
     cpu->dreg || cpu->freg || cpu->xmm || cpu->ilist || cpu->decoder)) {
    goto memory_error;
  }


  return cpu;

  memory_error:
  fprintf(stderr, "%Memory error\n");
  exit(1);

}


void reset_cpu(CPUx86 *cpu) {
  cpu->eflags  = 0x00000002;
  cpu->eip     = 0x0000fff0;
  cpu->new_eip_set = false;
  cpu->new_eip = 0;

  cpu->seg[CS].selector = 0xf000;
  cpu->seg[CS].base_address = 0xffff0000;
  cpu->seg[CS].limit = 0xffff;
  cpu->seg[CS].access_rights = SEGMENT_AR_PRESENT | SEGMENT_AR_DCTYPE_WR |
                               SEGMENT_AR_DCTYPE_A;
  int tmp_segments[5] = {SS, DS, ES, FS, GS};
  for (int i = 0; i > 5; ++i) {
    SegmentReg *tmp_seg = &(cpu->seg[tmp_segments[i]]);
    tmp_seg->selector = 0x0000;
    tmp_seg->base_address = 0x00000000;
    tmp_seg->limit = 0xffff;
    tmp_seg->access_rights = SEGMENT_AR_PRESENT | SEGMENT_AR_DCTYPE_WR | 
                            SEGMENT_AR_DCTYPE_A;
  }

  cpu->gdtr->base_address = 0x00000000;
  cpu->gdtr->limit = 0xffff;
  cpu->gdtr->access_rights = SEGMENT_AR_PRESENT | SEGMENT_AR_SYSTYPE_LDT;
  cpu->idtr->base_address = 0x00000000;
  cpu->idtr->limit = 0xffff;
  cpu->idtr->access_rights = SEGMENT_AR_PRESENT | SEGMENT_AR_SYSTYPE_LDT;
  cpu->ldtr->selector = 0x0000;
  cpu->ldtr->base_address = 0x00000000;
  cpu->ldtr->limit = 0xffff;
  cpu->ldtr->access_rights = SEGMENT_AR_PRESENT | SEGMENT_AR_SYSTYPE_LDT;
  cpu->tr->selector = 0x0000;
  cpu->tr->base_address = 0x00000000;
  cpu->tr->limit = 0xffff;
  cpu->tr->access_rights = SEGMENT_AR_PRESENT | SEGMENT_AR_SYSTYPE_LDT;

  for (int i = 0; i < 8; ++i) {
    cpu->gpr[i] = 0;

    for (int j = 0; j < 10; ++j) {
      cpu->freg[i].part[j] = 0;
    }

    for (int j = 0; j < 16; ++j) {
      cpu->xmm[i].part[j] = 0;
    }
  }

  cpu->creg[CR0] = 0x60000010;
  cpu->creg[CR2] = 0x00000000;
  cpu->creg[CR3] = 0x00000000;
  cpu->creg[CR4] = 0x00000000;

  cpu->dreg[DR0] = 0x00000000;
  cpu->dreg[DR1] = 0x00000000;
  cpu->dreg[DR2] = 0x00000000;
  cpu->dreg[DR3] = 0x00000000;
  cpu->dreg[DR6] = 0x00000000;
  cpu->dreg[DR7] = 0x00000000;

  cpu->fctrl = 0x0040;
  cpu->fstatus = 0x0000;
  cpu->ftag = 0x5555;
  cpu->fopcode = 0x00;
  cpu->fcs = 0x0000;
  cpu->fds = 0x0000;
  cpu->fip = 0x00000000;
  cpu->fdp = 0x00000000;

  cpu->mxcsr = SSE_MXCSR_IEEE754_MASKS_MASK; // all mask flags set

  cpu->operation_mode = OPERATION_REAL_MODE;
  cpu->paging_mode = PAGING_NO;
  cpu->interrupt_signal = 0;
  cpu->interrupt_service = 0;

  return;
}



void cpu_update(CPUx86 *cpu) {
  /*
   * Operating Mode service 
   */
  if (cpu->creg[CR0] & CR0_PAGING) {
    cpu->operation_mode = OPERATION_PROTECTED_MODE;
  }
  else {
    cpu->operation_mode = OPERATION_REAL_MODE;
  }

  /*
   * TODO: Paging Mode service
   */

//  /*
//   * Interrupt service 
//   */
//  if (cpu->interrupt_service == RUN_INTERRUPT) {
//    // TODO: rewrite to interrupt.c to more release form... 
//
//    SegmentReg temp_int_desc;
//    switch (cpu->operation_mode) {
//      case OPERATION_REAL_MODE: {
//        if (SEG_load_ivt_entry(cpu, cpu->interrupt_signal, &temp_int_desc) == NULL) {
//          return;
//        }
//
//        uint16_t temp_ip = cpu->eip & 0xffff;
//        uint16_t temp_cs = cpu->seg[CS]->selector;
//        uint16_t temp_flags = cpu->eflags & 0xffff;
//        
//        /* 
//        uint64_t stack_phy_addr = get_physical_addr(cpu, SS, cpu->gpr[ESP]);      
//        */
//        uint32_t stack_addr = SEG_get_linear_addr(cpu, cpu->seg[SS], SS, cpu->gpr[ESP]); // TODO: catch exceptions!
//        uint64_t stack_phy_addr = PAG_get_physical_addr(cpu, stack_addr);
//        PHYMEM_le_store_word(cpu->phy_mem, stack_phy_addr,     temp_ip);
//        PHYMEM_le_store_word(cpu->phy_mem, stack_phy_addr + 2, temp_cs);
//        PHYMEM_le_store_word(cpu->phy_mem, stack_phy_addr + 4, temp_flags);
//        cpu->gpr[ESP] += 6;
//
//        uint16_t flags_mask = ~(EFLAGS_ALIGNMENT_CHECK | EFLAGS_RESUME_FLAG | 
//            EFLAGS_TRAP_FLAG | EFLAGS_INTERRUPT_FLAG);
//        cpu->eflags &= flags_mask;
//
//        cpu->seg[CS]->selector = temp_int_desc->selector;
//        cpu->eip = temp_int_desc->base_address;
//
//      } 
//      case OPERATION_PROTECTED_MODE: {
//        if (SEG_load_idt_descriptor(cpu, cpu->interrupt_signal, &temp_int_desc) == NULL) {
//          return;
//        }
//
//
//
//
//
//
//
//
//
//      }
//    }
//  }
//
  /*
   * Decoder
   */
  Decoder *decoder = cpu->decoder;
  memset(decoder, 0, sizeof(Decoder));

  //puts("A");
  decode_opcode(cpu);
  //puts("B");
  switch (decoder->map) {
    case 0: {
      call_instruction_map0(cpu);
      break;
    }
    //case 1: {
    //  call_instruction_map1(cpu);
    //  break;
    //}

  }

  if (cpu->new_eip_set) {
    cpu->eip = cpu->new_eip;
  }
  else {
    cpu->eip += decoder->decode_flags & DECODER_BYTES_CNT;
  }
  cpu->new_eip_set = false;

  







}



int get_arg_size(int operation_mode, bool prefix_34) {
  bool arg = false;
  switch (operation_mode) {
    case OPERATION_REAL_MODE: arg = false; break;
    case OPERATION_PROTECTED_MODE: arg = true; break;
  }

  return (arg ^ prefix_34) ? DWORD : WORD;
}

int decode_segreg_idx(uint8_t byte) {
  int segreg = NULL_ARG;
  switch (byte) {
    case 0x26: segreg = ES; break;
    case 0x2e: segreg = CS; break;
    case 0x36: segreg = SS; break;
    case 0x3e: segreg = DS; break;
    case 0x64: segreg = FS; break;
    case 0x65: segreg = GS; break;
  }

  return segreg;
}


void decode_opcode(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  Instr_one *instr = cpu->ilist->instr;
  uint64_t code_phy_addr = get_physical_addr(cpu, CS, cpu->eip);
  //printf("CPA: %x\n", code_phy_addr);

  size_t instr_idx;
  uint8_t instr_bytes = 0;

  enum DECODER_STATE {
    ONE_BYTE_MAP = 0,
    TWO_BYTE_MAP,
    THREE_BYTE_MAP,
    EXIT
  } decoder_state = ONE_BYTE_MAP;

  // prefix phase
  while (instr_bytes <= 15) {
    uint8_t byte = PHYMEM_le_load_byte(cpu->phy_mem, code_phy_addr + instr_bytes);
    ++instr_bytes;
    //printf("C: %i %x\n", instr_bytes, byte);

    instr_idx = ILIST_get_idx(cpu, decoder->map, byte, NULL_ARG, NULL_ARG, NULL_ARG, NULL_ARG);
    if (instr_idx == -1LL) {
      // TODO: UD exception
      return;
    }

    uint8_t instr_special = instr[instr_idx].special;
    //printf("I: %i %x\n", instr_idx, instr_special);

    switch (decoder_state) {
      case ONE_BYTE_MAP: {
        switch (instr_special & INSTR_SPECIAL_FUNC) {
          case INSTR_ESCAPE_FUNC: {
            decoder->map = instr_special & INSTR_MAP_SELECTOR;
            decoder_state = TWO_BYTE_MAP;
            break;
          }

          case INSTR_PREFIX_FUNC: {
            decoder->mandatory_prefix = instr_special & INSTR_MANDPFX_SELECTOR;
            switch (instr_special & INSTR_PFXGRP_SELECTOR) {
              case 0: decoder->prefix_1 = byte; break;
              case 1: decoder->prefix_2 = byte; break;
              case 2: decoder->prefix_3 = byte; break;
              case 3: decoder->prefix_4 = byte; break;
            }
  
            break;
          }

          default: {
            decoder->opcode = byte;
            decoder_state = EXIT;
          }
        }
  
        break;
      }

      case TWO_BYTE_MAP: {
        if ((instr_special & INSTR_SPECIAL_FUNC) == INSTR_ESCAPE_FUNC) {
          decoder->map = instr_special & INSTR_MAP_SELECTOR;
          decoder_state = THREE_BYTE_MAP;
        }
        else {
          decoder->opcode = byte;
          decoder_state = EXIT;
        }

        break;
      }

      case THREE_BYTE_MAP: {
        decoder->opcode = byte;
        decoder_state = EXIT;

        break;
      }
    }

    if (decoder_state == EXIT) {
      break;
    }
  }
  decoder->instr_idx = instr_idx;
  UPDATE_DECODER_BYTES_CNT(instr_bytes);  

  // TODO: exception if instr_bytes > 15

  uint8_t opcbits = instr[instr_idx].opcbits;
  if (opcbits != NULL_ARG) {
    uint8_t opc_mask = (0xff << (8 - opcbits) & 0xff);
    decoder->opc_arg = decoder->opcode & ~(opc_mask);
    decoder->opcode &= opc_mask;
  }

  decoder->segment_code = NULL_ARG;

  decoder->arg_size = get_arg_size(cpu->operation_mode, (decoder->prefix_3 != 0));
  decoder->addr_size = get_arg_size(cpu->operation_mode, (decoder->prefix_4 != 0));

  if ((instr[instr_idx].mod == 255) &&
      (instr[instr_idx].nnn == 255) && 
      (instr[instr_idx].rm == 255)) {
    return;
  }

  // load modrm
  decode_modrm(cpu);
  instr_idx = ILIST_get_idx(cpu, decoder->map, decoder->opcode, 
    decoder->mandatory_prefix, decoder->mod, decoder->nnn, decoder->rm);
  if (instr_idx == -1) {
    // TODO: UD exception
    return;
  }

  return;
}


void decode_modrm(CPUx86 *cpu) {
  Decoder *decoder = cpu->decoder;
  //Instr_one *instr = cpu->ilist->instr;
  uint64_t code_phy_addr = get_physical_addr(cpu, CS, cpu->eip);
  uint8_t instr_bytes = decoder->decode_flags & DECODER_BYTES_CNT;

  uint8_t modrm = PHYMEM_le_load_byte(cpu->phy_mem, code_phy_addr + instr_bytes);
  ++instr_bytes;

  // TODO: exception (instr_bytes > 15)

  decoder->mod = (modrm & 0b11000000) >> 6;
  decoder->nnn = (modrm & 0b00111000) >> 3;
  decoder->rm  = (modrm & 0b00000111);

  if (decoder->addr_size == 0) {
    decoder->addr_size = get_arg_size(cpu->operation_mode, (decoder->prefix_4 != 0));
  }

  int disp_size = 0;
  bool disp_sign_extend = false;
  bool sib_load = false;

  switch (decoder->addr_size) {
    case WORD: {
      switch (decoder->mod) {
        case 0: {
          if (decoder->rm == 6) {
            disp_size = WORD;
            decoder->decode_flags |= DECODER_RMDISP;
          }
          else if ((decoder->rm == 2) || (decoder->rm == 3)) {
            decoder->decode_flags |= DECODER_STACKREG;
          }

          break;
        }

        case 1: {
          disp_size = BYTE;
          if (decoder->rm == 0) {
            disp_sign_extend = true;
          }
          else if ((decoder->rm == 2) || (decoder->rm == 3) || (decoder->rm == 6)) {
            decoder->decode_flags |= DECODER_STACKREG;
          }

          break;
        }

        case 2: {
          disp_size = WORD;
          if ((decoder->rm == 2) || (decoder->rm == 3) || (decoder->rm == 6)) {
            decoder->decode_flags |= DECODER_STACKREG;
          }

          break;
        }
      }

      break;
    }

    case DWORD: {
      if (decoder->rm == 4) {
        sib_load = true;
      }

      switch (decoder->mod) {
        case 0: {
          if (decoder->rm == 5) {
            disp_size = DWORD;
            decoder->decode_flags |= DECODER_RMDISP;
          }

          break;
        }

        case 1: {
          disp_size = BYTE;
          if (decoder->rm == EAX) {
            disp_sign_extend = true;
          }

          else if (decoder->rm == EBP) {
            decoder->decode_flags |= DECODER_STACKREG;
          }

          break;
        } 

        case 2: {
          disp_size = DWORD;
          if (decoder->rm == EBP) {
            decoder->decode_flags |= DECODER_STACKREG;
          }
          break;
        }

        case 3: {
          sib_load = false;
          break;
        } 
      }
    }

    break;
  }

  decoder->decode_flags |= DECODER_MODRM;

  if (sib_load) {
    uint8_t sib = PHYMEM_le_load_byte(cpu->phy_mem, code_phy_addr + instr_bytes);
    ++instr_bytes;

    // TODO: exception (instr_bytes > 15)

    decoder->scale = (sib & 0b11000000) >> 6;
    decoder->index = (sib & 0b00111000) >> 3;
    decoder->base  = (sib & 0b00000111);

    if (decoder->base == EBP) {
      if (decoder->mod == 0) {
        disp_size = DWORD;
        decoder->decode_flags |= DECODER_SIBEBPDISP;
      }
      else {
        decoder->decode_flags |= DECODER_STACKREG;
      }
    }

    decoder->decode_flags |= DECODER_SIB;
  }

  switch (disp_size) {
    case BYTE: {
      uint8_t disp8 = PHYMEM_le_load_byte(cpu->phy_mem, code_phy_addr + instr_bytes);
      instr_bytes += BYTE;

      if (disp_sign_extend) {
        decoder->disp = (int32_t)((int8_t)disp8);
      }
      else {
        decoder->disp = (uint32_t)disp8;
      }

      decoder->decode_flags |= DECODER_DISP;
      break;
    }

    case WORD: {
      uint16_t disp16 = PHYMEM_le_load_word(cpu->phy_mem, code_phy_addr + instr_bytes);
      instr_bytes += WORD;

      decoder->disp = (uint32_t)disp16;
      decoder->decode_flags |= DECODER_DISP;
      break;
    }

    case DWORD: {
      uint32_t disp32 = PHYMEM_le_load_dword(cpu->phy_mem, code_phy_addr + instr_bytes);
      instr_bytes += DWORD;

      decoder->disp = disp32;
      decoder->decode_flags |= DECODER_DISP;
      break;
    }
  }

  // TODO: exception (instr_btes > 15)

  UPDATE_DECODER_BYTES_CNT(instr_bytes);

  return;
}

void decode_imm(CPUx86 *cpu, int imm_size) {
  Decoder *decoder = cpu->decoder;
  //Instr_one *instr = cpu->ilist->instr;
  uint64_t code_phy_addr = get_physical_addr(cpu, CS, cpu->eip);
  uint8_t instr_bytes = decoder->decode_flags & DECODER_BYTES_CNT;

  uint32_t imm;
  switch (imm_size) {
    case BYTE: {
      imm = (uint32_t)PHYMEM_le_load_byte(cpu->phy_mem, code_phy_addr + instr_bytes);
      instr_bytes += BYTE;
      break;
    }

    case WORD: {
      imm = (uint32_t)PHYMEM_le_load_word(cpu->phy_mem, code_phy_addr + instr_bytes);
      instr_bytes += WORD;
      break;
    } 

    case DWORD:
    default: {
      imm = (uint32_t)PHYMEM_le_load_dword(cpu->phy_mem, code_phy_addr + instr_bytes);
      instr_bytes += DWORD;
      break;
    } 
  }

  decoder->imm = imm;
  decoder->decode_flags |= DECODER_IMM;
  
  // TODO: exception (instr_bytes > 15)

  UPDATE_DECODER_BYTES_CNT(instr_bytes);

  return;
}


uint32_t load_gpr(CPUx86 *cpu, int reg, int size) {
  uint32_t value;
  uint32_t mask; 

  switch (size) {
    case BYTE: {
      value = cpu->gpr[reg & 0b011];
      mask = 0x000000ff;
      if (reg & 0b100) {
        value >>= 8;
      }
      
      break;
    }

    case WORD: {
      value = cpu->gpr[reg];
      mask = 0x0000ffff;
      break;
    }

    case DWORD: {
      value = cpu->gpr[reg];
      mask = 0xffffffff;
      break;
    }
  }

  return value & mask;
}

void store_gpr(CPUx86 *cpu, int reg, int size, uint32_t value) {
  switch (size) {
    case BYTE: {
      int reg8 = reg & 0b011;
      if (reg & 0b100) {
        uint32_t mask = 0xffff00ff;
        cpu->gpr[reg8] &= mask;
        cpu->gpr[reg8] |= (value << 8) & ~mask; 
      }
      else {
        uint32_t mask = 0xffffff00;
        cpu->gpr[reg8] &= mask;
        cpu->gpr[reg8] |= value & ~mask;
      }
      
      break;
    }
  
    case WORD: {
      uint32_t mask = 0xffff0000;
      cpu->gpr[reg] &= mask;
      cpu->gpr[reg] |= value & ~mask;
      break;
    }
  
    case DWORD: {
      cpu->gpr[reg] = value;
      break;
    }
  }
  return;
}

uint32_t decode_logical_addr(CPUx86 *cpu, int *segment) {
  Decoder *decoder = cpu->decoder;

  int segment_code = DS;
  uint32_t effective_addr = 0;
  int decode_flags = decoder->decode_flags;

  switch (decoder->addr_size) {
    case WORD: {
      if (decode_flags & DECODER_DISP) {
        effective_addr += decoder->disp;
      }

      if (!(decode_flags & DECODER_RMDISP)) {
        switch (decoder->rm) {
          case 0: { 
            effective_addr += load_gpr(cpu, BX, WORD) + load_gpr(cpu, SI, WORD);
            break;
          }
          case 1: { 
            effective_addr += load_gpr(cpu, BX, WORD) + load_gpr(cpu, DI, WORD);
            break;
          }
          case 2: { 
            effective_addr += load_gpr(cpu, BP, WORD) + load_gpr(cpu, SI, WORD);
            break;
          }
          case 3: { 
            effective_addr += load_gpr(cpu, BP, WORD) + load_gpr(cpu, DI, WORD);
            break;
          }
          case 4: { 
            effective_addr += load_gpr(cpu, SI, WORD);
            break;
          }
          case 5: { 
            effective_addr += load_gpr(cpu, DI, WORD);
            break;
          }
          case 6: { 
            effective_addr += load_gpr(cpu, BP, WORD);
            break;
          }
          case 7: { 
            effective_addr += load_gpr(cpu, BX, WORD);
            break;
          }
        }
      }

      break;
    } 

    case DWORD: {
      if (decode_flags & DECODER_DISP) {
        effective_addr += decoder->disp;
      }
  
      if (!(decode_flags & (DECODER_RMDISP | DECODER_SIB))) {
        effective_addr += load_gpr(cpu, decoder->rm, DWORD);
      }
      else if (decode_flags & DECODER_SIB) {
        uint32_t index_value = 0;
        if (decoder->index != ESP) {
          index_value = load_gpr(cpu, decoder->index, DWORD);
        }

        uint32_t base_value = 0;
        if (!(decode_flags & DECODER_SIBEBPDISP)) {
          base_value = load_gpr(cpu, decoder->base, DWORD);
        }

        effective_addr += (index_value << decoder->scale) + base_value;
      }

      break;
    } 
  }

  if (decoder->segment_code == NULL_ARG) {
    segment_code = decode_segreg_idx(decoder->prefix_2);
    if (segment_code == NULL_ARG) {
      if (decoder->decode_flags & DECODER_STACKREG) {
       segment_code = SS;
      }
    }
  }
  else {
    segment_code = decoder->segment_code;
  }

  if (segment != NULL) {
    *segment = segment_code;
  }

  return effective_addr;
}


uint32_t load_rm(CPUx86 *cpu, int size) {
  Decoder *decoder = cpu->decoder;
  
  uint32_t value;

  if (decoder->mod == 3) {
    value = load_gpr(cpu, decoder->rm, size);
  }
  else {
    int segment_code;
    uint32_t effective_addr = decode_logical_addr(cpu, &segment_code);    
    uint64_t data_phy_addr = get_physical_addr(cpu, segment_code, effective_addr);

    switch (size) {
      case BYTE: {
        value = (uint32_t)PHYMEM_le_load_byte(cpu->phy_mem, data_phy_addr);
        break;
      }
      case WORD: {
        value = (uint32_t)PHYMEM_le_load_word(cpu->phy_mem, data_phy_addr);
        break;
      }
      case DWORD: {
        value = PHYMEM_le_load_dword(cpu->phy_mem, data_phy_addr);
        break;
      } 
    }
  }

  return value;
}

void store_rm(CPUx86 *cpu, int size, uint32_t value) {
  Decoder *decoder = cpu->decoder;
  
  if (decoder->mod == 3) {
    store_gpr(cpu, decoder->rm, size, value);
  }
  else {
    int segment_code;
    uint32_t effective_addr = decode_logical_addr(cpu, &segment_code);    
    uint64_t data_phy_addr = get_physical_addr(cpu, segment_code, effective_addr);
    
    switch (size) {
      case BYTE: {
        PHYMEM_le_store_byte(cpu->phy_mem, data_phy_addr, (uint8_t)(value & 0xff));
        break;
      }
      case WORD: {
        PHYMEM_le_store_word(cpu->phy_mem, data_phy_addr, (uint16_t)(value & 0xffff));
        break;
      }
      case DWORD: {
        PHYMEM_le_store_dword(cpu->phy_mem, data_phy_addr, value);
        break;
      } 
    }
  }

  return;
}

bool check_eflags_with_cc(CPUx86 *cpu, uint8_t cc) {
  bool neg_flag = cc & 0b0001;
  uint8_t code = cc & 0b1110;
  uint32_t eflags = cpu->eflags;

  bool overflow_flag = eflags & EFLAGS_OVERFLOW_FLAG;
  bool sign_flag =     eflags & EFLAGS_SIGN_FLAG;
  bool zero_flag =     eflags & EFLAGS_ZERO_FLAG;
  bool adjust_flag =   eflags & EFLAGS_ADJUST_FLAG;
  bool parity_flag =   eflags & EFLAGS_PARITY_FLAG;
  bool carry_flag =    eflags & EFLAGS_CARRY_FLAG;

  bool test_flag = 0;
  switch (code) {
    case 0b0000: test_flag = overflow_flag; break; /* overflow */
    case 0b0010: test_flag = carry_flag; break; /* below */
    case 0b0100: test_flag = zero_flag; break; /* above or equal */
    case 0b0110: test_flag = carry_flag | zero_flag; break; /* below or equal */
    case 0b1000: test_flag = sign_flag; break; /* sign */
    case 0b1010: test_flag = parity_flag; break; /* parity */
    case 0b1100: test_flag = sign_flag ^ overflow_flag; break; /* less */
    case 0b1110: test_flag = (sign_flag ^ overflow_flag) | zero_flag; break; /* less or equal */
  }

  return test_flag ^ neg_flag;
}


uint64_t get_physical_addr(CPUx86 *cpu, int segment_code, uint64_t effective_addr) {
  SegmentReg *segment = &(cpu->seg[segment_code]);

  uint32_t linear_addr = SEG_get_linear_addr(cpu, segment, segment_code, effective_addr);
  uint64_t physical_addr = PAG_get_physical_addr(cpu, linear_addr);
  return physical_addr;
}


