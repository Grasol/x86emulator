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

#include "cpu.h"

uint32_t SEG_get_linear_addr(CPUx86 *cpu, SegmentReg *segment, int segment_code, uint32_t logical_offset);

bool SEG_check_limit(SegmentReg *segment, uint32_t logical_offset, int size);
SegmentReg *SEG_load_gdt_ldt_descriptor(CPUx86 *cpu, uint16_t selector, SegmentReg *segment);
SegmentReg *SEG_load_idt_ivt_descriptor(CPUx86 *cpu, uint8_t interrupt_vector, SegmentReg *segment);
SegmentReg *SEG_load_ivt_entry(CPUx86 *cpu, uint8_t interrupt_vector, SegmentReg *segment);
SegmentReg *SEG_load_descriptor_from_table(CPUx86 *cpu, uint32_t table_addr, 
    uint16_t selector, SegmentReg *segment);


