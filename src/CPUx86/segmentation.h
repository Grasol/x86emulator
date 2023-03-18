#pragma once

#include "cpu.h"

uint32_t SEG_get_linear_addr(CPUx86 *cpu, SegmentReg *segment, int segment_code, uint32_t logical_offset);

bool SEG_check_limit(SegmentReg *segment, uint32_t logical_offset, int size);
SegmentReg *SEG_load_gdt_ldt_descriptor(CPUx86 *cpu, uint16_t selector, SegmentReg *segment);
SegmentReg *SEG_load_idt_ivt_descriptor(CPUx86 *cpu, uint8_t interrupt_vector, SegmentReg *segment);
SegmentReg *SEG_load_ivt_entry(CPUx86 *cpu, uint8_t interrupt_vector, SegmentReg *segment);
SegmentReg *SEG_load_descriptor_from_table(CPUx86 *cpu, uint32_t table_addr, 
    uint16_t selector, SegmentReg *segment);


