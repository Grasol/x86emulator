#pragma once

#include "cpu.h"

void call_instruction_map0(CPUx86 *cpu);

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