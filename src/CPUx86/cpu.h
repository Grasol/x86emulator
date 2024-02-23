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

#pragma once

#include "includes.h"
#include "open_file.h"
#include "phymem.h"

#define BYTE 1
#define WORD 2
#define DWORD 4
#define QWORD 8
#define XWORD 16

#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

#define AX 0
#define CX 1
#define DX 2
#define BX 3
#define SP 4
#define BP 5
#define SI 6
#define DI 7

#define AL 0
#define CL 1
#define DL 2
#define BL 3
#define AH 4
#define CH 5
#define DH 6
#define BH 7

#define ES 0
#define CS 1
#define SS 2
#define DS 3
#define FS 4
#define GS 5

#define CR0 0
#define CR2 2
#define CR3 3
#define CR4 4

#define DR0 0
#define DR1 1
#define DR2 2
#define DR3 3
#define DR6 6
#define DR7 7


#pragma pack(4)
struct SegmentReg {
  uint32_t base_address;
  uint32_t limit;
  uint16_t access_rights;
  uint16_t selector;
};
typedef struct SegmentReg SegmentReg;

#define SEGMENT_SEL_TABLE_INDICATOR  0x0004
#define SEGMENT_SEL_PRIVILEGE_LEVEL  0x0003
#define SEGMENT_AR_GRANULARITY       0x8000
#define SEGMENT_AR_OPERATION_SIZE    0x4000
#define SEGMENT_AR_PRESENT           0x0080
#define SEGMENT_AR_DPL_MASK          0x0060
#define SEGMENT_AR_SYSTEM            0x0010
#define SEGMENT_AR_DCTYPE_E          0x0008
#define SEGMENT_AR_DCTYPE_EC         0x0004
#define SEGMENT_AR_DCTYPE_WR         0x0002
#define SEGMENT_AR_DCTYPE_A          0x0001
#define SEGMENT_AR_SYSTYPE_GATETYPE  0x0004
#define SEGMENT_AR_SYSTYPE_TSS_A_16  0x0001
#define SEGMENT_AR_SYSTYPE_LDT       0x0002
#define SEGMENT_AR_SYSTYPE_TSS_B_16  0x0003
#define SEGMENT_AR_SYSTYPE_CALL_16   0x0004
#define SEGMENT_AR_SYSTYPE_TASK      0x0005
#define SEGMENT_AR_SYSTYPE_INT_16    0x0006
#define SEGMENT_AR_SYSTYPE_TRAP_16   0x0007
#define SEGMENT_AR_SYSTYPE_TSS_A_32  0x0009
#define SEGMENT_AR_SYSTYPE_TSS_B_32  0x000b
#define SEGMENT_AR_SYSTYPE_CALL_32   0x000c
#define SEGMENT_AR_SYSTYPE_INT_32    0x000e
#define SEGMENT_AR_SYSTYPE_TRAP_32   0x000f

struct FPUReg {
  uint8_t part[10];
};
typedef struct FPUReg FPUReg;

#define FPU_IEEE754_ROUDING_NEAREST  0
#define FPU_IEEE754_ROUDING_DOWN     1
#define FPU_IEEE754_ROUDING_UP       2
#define FPU_IEEE754_ROUDING_TRUNCATE 3
#define FPU_CONTROL_PRECISION_SINGLE   0
#define FPU_CONTROL_PRECISION_DOUBLE   2
#define FPU_CONTROL_PRECISION_EXTENDED 3
#define FPU_CONTROL_REG_ROUNDING_MASK    0x0c00
#define FPU_CONTROL_REG_PRECISION_MASK   0x0300
#define FPU_CONTROL_REG_INFINITY         0x1000
#define FPU_CONTROL_REG_MASKS_PRECISION  0x0020
#define FPU_CONTROL_REG_MASKS_UNDERFLOW  0x0010
#define FPU_CONTROL_REG_MASKS_OVERFLOW   0x0008
#define FPU_CONTROL_REG_MASKS_ZERODIVIDE 0x0004
#define FPU_CONTROL_REG_MASKS_DENORMAL   0x0002
#define FPU_CONTROL_REG_MASKS_INVALID    0x0001

#define FPU_STATUS_REG_BUSY                  0x8000
#define FPU_STATUS_REG_CC_MASK               0x4700
#define FPU_STATUS_REG_TOP_OF_STACK_PTR_MASK 0x3800
#define FPU_STATUS_REG_SUMMARY_EXCEPTIONS    0x0080
#define FPU_STATUS_REG_STACK_FAULT           0x0040
#define FPU_STATUS_REG_EXCEPTIONS_PRECISION  0x0020
#define FPU_STATUS_REG_EXCEPTIONS_UNDERFLOW  0x0010
#define FPU_STATUS_REG_EXCEPTIONS_OVERFLOW   0x0008
#define FPU_STATUS_REG_EXCEPTIONS_ZERODIVIDE 0x0004
#define FPU_STATUS_REG_EXCEPTIONS_DENORMAL   0x0002
#define FPU_STATUS_REG_EXCEPTIONS_INVALID    0x0001
#define FPU_IEEE754_FLAGS_MASK               0x003f

#define FPU_TAG_VALID 0
#define FPU_TAG_ZERO 1
#define FPU_TAG_SPECIAL 2
#define FPU_TAG_EMPTY 3

struct SSEReg {
  uint8_t part[16];
};
typedef struct SSEReg SSEReg;

#define SSE_MXCSR_FLUSH_TO_ZERO           0x00008000
#define SSE_MXCSR_ROUNDING_MASK           0x00006000
#define SSE_MXCSR_MASKS_PRECISION         0x00001000
#define SSE_MXCSR_MASKS_UNDERFLOW         0x00000800
#define SSE_MXCSR_MASKS_OVERFLOW          0x00000400
#define SSE_MXCSR_MASKS_ZERODIVIDE        0x00000200
#define SSE_MXCSR_MASKS_DENORMAL          0x00000100
#define SSE_MXCSR_MASKS_INVALID           0x00000080
#define SSE_MXCSR_DENORMALS_ARE_ZEROS     0x00000040
#define SSE_MXCSR_EXCEPTIONS_PRECISION    0x00000020
#define SSE_MXCSR_EXCEPTIONS_UNDERFLOW    0x00000010
#define SSE_MXCSR_EXCEPTIONS_OVERFLOW     0x00000008
#define SSE_MXCSR_EXCEPTIONS_ZERODIVIDE   0x00000004
#define SSE_MXCSR_EXCEPTIONS_DENORMAL     0x00000002
#define SSE_MXCSR_EXCEPTIONS_INVALID      0x00000001
#define SSE_MXCSR_IEEE754_MASKS_MASK      0x00001f80
#define SSE_MXCSR_IEEE754_EXCEPTIONS_MASK 0x0000003f

struct Instr_one {
  uint8_t map;
  uint8_t pfx;
  uint8_t opcode;
  uint8_t mod;
  uint8_t nnn;
  uint8_t rm;
  uint8_t special;
  uint8_t opcbits;
};
typedef struct Instr_one Instr_one;

struct Instr_list {
  Instr_one *instr;
  size_t cnt;
};
typedef struct Instr_list Instr_list;

struct Decoder {
  size_t instr_idx;
  #define DECODER_BYTES_CNT  0x000f
  #define DECODER_MODRM      0x0010
  #define DECODER_SIB        0x0020
  #define DECODER_DISP       0x0040
  #define DECODER_IMM        0x0080
  #define DECODER_RMDISP     0x0100
  #define DECODER_SIBEBPDISP 0x0200
  #define DECODER_STACKREG   0x0400
  int decode_flags;
  int arg_size;
  int addr_size;
  int segment_code;

  uint32_t disp;
  uint32_t imm;
  uint8_t mod;
  uint8_t nnn;
  uint8_t rm;
  uint8_t scale;
  uint8_t index;
  uint8_t base;
  uint8_t opc_arg;

  uint8_t prefix_1;
  uint8_t prefix_2;
  uint8_t prefix_3;
  uint8_t prefix_4;
  uint8_t mandatory_prefix;
  uint8_t map;
  uint8_t opcode;
};
typedef struct Decoder Decoder;

#define UPDATE_DECODER_BYTES_CNT(val) \
decoder->decode_flags &= ~DECODER_BYTES_CNT; \
decoder->decode_flags |= val & DECODER_BYTES_CNT;

#pragma pack(8)
struct CPUx86 {
  // EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI
  uint32_t *gpr;
  uint32_t eflags;
  uint32_t eip;
  uint32_t new_eip;
  bool new_eip_set;

  // ES, CS, SS, DS, FS, GS
  SegmentReg *seg;
  SegmentReg *gdtr, *ldtr, *idtr, *tr;
  uint32_t *creg;

  uint32_t *dreg;

  // x87
  // ST(0) - ST(7)
  FPUReg *freg;
  uint16_t fctrl;
  uint16_t fstatus;
  uint16_t ftag;
  uint16_t fopcode;
  
  uint16_t fcs;
  uint16_t fds;
  uint32_t fip;
  uint32_t fdp;

  // SSE
  // XMM0 - XMM7
  SSEReg *xmm;
  uint32_t mxcsr;


  #define OPERATION_REAL_MODE 0
  #define OPERATION_PROTECTED_MODE 1
  // TODO: Virtual Mode, SMM, Long Mode
  // #define OPERATION_VIRTUAL_MODE 2
  // #define OPERATION_SMM 3
  // #define OPERATION_COMPATIBILITY_MODE 4
  // #define OPERATION_64BIT_MODE 5
  int operation_mode;

  #define PAGING_NO 0
  #define PAGING_32BIT 1
  #define PAGING_PAE 2
  int paging_mode;

  #define INTERRUPT_DE 0
  #define INTERRUPT_DB 1
  #define INTERRUPT_NMI 2
  #define INTERRUPT_BP 3
  #define INTERRUPT_OF 4
  #define INTERRUPT_BR 5
  #define INTERRUPT_UD 6
  #define INTERRUPT_NM 7
  #define INTERRUPT_DF 8
  #define INTERRUPT_TS 10
  #define INTERRUPT_NP 11
  #define INTERRUPT_SS 12
  #define INTERRUPT_GP 13
  #define INTERRUPT_PF 14
  #define INTERRUPT_MF 16
  #define INTERRUPT_AC 17
  #define INTERRUPT_MC 18
  #define INTERRUPT_XM 19
  int interrupt_signal;
  #define NO_INTERRUPT 0
  #define RUN_INTERRUPT 1
  // TODO: FIRST_INTERRUPT 1
  // SECOND_INTERRUPT 2
  #define TRIPLE_FAULT 3
  int interrupt_service;

  Instr_list *ilist;
  Decoder *decoder;
  PhyMem *phy_mem;
};
typedef struct CPUx86 CPUx86;

#define EFLAGS_ID                        0x00200000
#define EFLAGS_VIRTUAL_INTERRUPT_PENDING 0x00100000
#define EFLAGS_VIRTUAL_INTERRUPT_FLAG    0x00080000
#define EFLAGS_ALIGNMENT_CHECK           0x00040000
#define EFLAGS_VIRTUAL_8086_MODE         0x00020000
#define EFLAGS_RESUME_FLAG               0x00010000
#define EFLAGS_NESTED_TASK               0x00004000
#define EFLAGS_IOPL_FIELD_MASK           0x00003000
#define EFLAGS_OVERFLOW_FLAG             0x00000800
#define EFLAGS_DIRECTION_FLAG            0x00000400
#define EFLAGS_INTERRUPT_FLAG            0x00000200
#define EFLAGS_TRAP_FLAG                 0x00000100
#define EFLAGS_SIGN_FLAG                 0x00000080
#define EFLAGS_ZERO_FLAG                 0x00000040
#define EFLAGS_ADJUST_FLAG               0x00000010
#define EFLAGS_PARITY_FLAG               0x00000004
#define EFLAGS_CARRY_FLAG                0x00000001
#define EFLAGS_STATUS_FLAGS              0x000008d5
#define UPDATE_EFLAGS(v, f) \
cpu->eflags &= ~f; \
cpu->eflags |= (v & f) | 0x2; 


#define CR0_PAGING              0x80000000
#define CR0_CACHE_DISABLE       0x40000000
#define CR0_NOT_WRITE_THROUGH   0x20000000
#define CR0_ALIGNMENT_MASK      0x00040000
#define CR0_WRITE_PROTECT       0x00010000
#define CR0_NUMERIC_ERROR       0x00000020
#define CR0_EXTENSION_TYPE      0x00000010
#define CR0_TASK_SWITCHED       0x00000008
#define CR0_EMULATION           0x00000004
#define CR0_MONITOR_COPROCESSOR 0x00000002
#define CR0_PROTECTION_ENABLE   0x00000001

#define CR3_PAGE_LEVEL_CACHE_DISABLE 0x00000010
#define CR3_PAGE_LEVEL_WRITE_THROUGH 0x00000008

#define CR4_USER_MODE_INSTRUCTION_PREVENTION      0x00000800
#define CR4_OSXMMEXCPT                            0x00000400
#define CR4_OSFXSR                                0x00000200
#define CR4_PERFORMANCE_MONITORING_COUNTER_ENABLE 0x00000100
#define CR4_PAGE_GLOBAL_ENABLE                    0x00000080
#define CR4_MACHINE_CHECK_ENABLE                  0x00000040
#define CR4_PHYSICAL_ADDRESS_EXTENSION            0x00000020
#define CR4_PAGE_SIZE_EXTENSIONS                  0x00000010
#define CR4_DEBUGGING_EXTENSIONS                  0x00000008
#define CR4_TIME_STAMP_DISABLE                    0x00000004
#define CR4_PROTECTED_MODE_VIRTUAL_INTERRUPTS     0x00000002
#define CR4_VIRTUAL_8086_MODE_EXTENSIONS          0x00000001

CPUx86 *CPUx86_init();
void reset_cpu(CPUx86 *cpu);
void cpu_update(CPUx86 *cpu);

#define FILE_NAME "instr_list.bin"
#define NULL_ARG 255

#define INSTR_SPECIAL_FUNC 0xf0
#define INSTR_PREFIX_FUNC 0x00
#define INSTR_ESCAPE_FUNC 0x10
#define INSTR_MANDPFX_SELECTOR 0x0c
#define INSTR_PFXGRP_SELECTOR 0x03
#define INSTR_MAP_SELECTOR 0x0f

Instr_list* ILIST_init();
size_t ILIST_get_idx(CPUx86 *cpu, uint8_t map, uint8_t opc, uint8_t pfx, uint8_t mod, uint8_t nnn, uint8_t rm);

int get_arg_size(int operation_mode, bool prefix_34);
int decode_segreg_idx(uint8_t byte);
void decode_opcode(CPUx86 *cpu);
void decode_modrm(CPUx86 *cpu);
void decode_imm(CPUx86 *cpu, int imm_size);
uint32_t load_gpr(CPUx86 *cpu, int reg, int size);
void store_gpr(CPUx86 *cpu, int reg, int size, uint32_t value);
uint32_t decode_logical_addr(CPUx86 *cpu, int *segment);
uint32_t load_rm(CPUx86 *cpu, int size);
void store_rm(CPUx86 *cpu, int size, uint32_t value);

bool check_eflags_with_cc(CPUx86 *cpu, uint8_t cc);

uint64_t get_physical_addr(CPUx86 *cpu, int segment, uint64_t effective_addr);

uint8_t  load_byte(CPUx86 *cpu, int segment, uint64_t effective_addr);
uint16_t load_word(CPUx86 *cpu, int segment, uint64_t effective_addr);
uint32_t load_dword(CPUx86 *cpu, int segment, uint64_t effective_addr);
uint64_t load_qword(CPUx86 *cpu, int segment, uint64_t effective_addr);

void store_byte(CPUx86 *cpu, int segment, uint64_t effective_addr, uint8_t data);
void store_word(CPUx86 *cpu, int segment, uint64_t effective_addr, uint16_t data);
void store_dword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint32_t data);
void store_qword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint64_t data);