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


int get_physical_addr(CPUx86 *cpu, int segment, uint64_t effective_addr, uint64_t *phy_addr);

int load_byte(CPUx86 *cpu, int segment, uint64_t effective_addr, uint8_t *data);
int load_word(CPUx86 *cpu, int segment, uint64_t effective_addr, uint16_t *data);
int load_dword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint32_t *data);
int load_qword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint64_t *data);

int store_byte(CPUx86 *cpu, int segment, uint64_t effective_addr, uint8_t data);
int store_word(CPUx86 *cpu, int segment, uint64_t effective_addr, uint16_t data);
int store_dword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint32_t data);
int store_qword(CPUx86 *cpu, int segment, uint64_t effective_addr, uint64_t data);


