#include "segmentation.h"


/*
 * Checks offset in limit of segment
 * if it returns false, caller must generate #GP or #SS exceptions
 */
//bool SEG_check_limit(SegmentReg *segment, uint32_t logical_offset, int size) {
//  bool res = true;
//  // calculates address of last byte, where logical_offset is first byte
//  uint32_t last_offset = logical_offset + size - 1;   
//
//  uint32_t limit = segment->limit;
//  uint16_t access = segment->access_rights;
//  if (access & SEGMENT_AR_GRANULARITY) {
//    limit <<= 12; // segment in 4-KByte increments
//    logical_offset &= 0xfffff000; // lower 12bits are not checked
//    last_offset &= 0xfffff000;
//  }
//
//  if (access & SEGMENT_AR_SYSTEM) { // Code/Data Type
//    if (access & SEGMENT_AR_EC) { // expand-down 
//      uint32_t max_limit = (access & SEGMENT_AR_OPERATION_SIZE) ? 0xffffffff : 0xffff;
//      if ((limit >= logical_offset) && (logical_offset < max_limit) ||
//          (limit >= last_offset) && (last_offset < max_limit)) {
//        bool res = false;
//      }
//    }
//    else { // expand-up
//      if ((logical_offset > limit) || (last_offset > limit)) {
//        bool res = false;
//      } 
//    }
//  }
//  else {
//    if (logical_offset > limit) || (last_offset > limit) {
//      bool res = false;
//    } 
//  }
//
//  return res;
//}
//
///*
// * Loads segment descriptor (by selector) to segment (in 3th arg) from GDT or LDT 
// * if selector is greater than descriptor table limit, it generates #GP exception
// * and returns NULL 
// */
//SegmentReg *SEG_load_gdt_ldt_descriptor(CPUx86 *cpu, uint16_t selector, SegmentReg *segment) {
//  int privilege_level = selector & SEGMENT_SEL_PRIVILEGE_LEVEL;
//  bool table_indicator = selector & SEGMENT_SEL_TABLE_INDICATOR;
//  selector &= 0xfff8;
//
//  uint32_t dt_base;
//  uint32_t dt_limit;
//  if (table_indicator) { // Local Descriptor Table
//    dt_base = cpu->ldtr->base_address;
//    dt_limit = cpu->ldrt->limit & 0xffff8;
//  }
//  else { // Global Descriptor Table
//    dt_base = cpu->gdtr->base_address;
//    dt_limit = cpu->gdtr->limit & 0xffff8;
//  }
//
//  if ((uint32_t)(selector + 7) > dt_limit) {
//    INT_set_interrupt(cpu, INTERRUPT_GP);
//    goto error_exit;
//  }
//
//  return SEG_get_descriptor_from_table(cpu, dt_base, selector, segment);
//
//  error_exit:
//  return NULL;
//}
//
///*
// * Loads descriptor from IDT
// * If interrupt vector is greater than limit of IDTR generates #GP exception and returns NULL
// * Also it can generetes all exceptions SEG_load_descriptor_from_table()
// */
//SegmentReg *SEG_load_idt_ivt_descriptor(CPUx86 *cpu, uint8_t interrupt_vector, SegmentReg *segment) {
//  uint32_t base = cpu->idtr->base_address;
//  uint32_t limit = cpu->idtr->limit;
//  uint32_t offset = interrupt_vector * 8;
//  uint32_t last_offset = offset + 7;
//
//   if (last_offset > limit) {
//    INT_set_interrupt(cpu, INTERRUPT_GP);
//    goto error_exit;
//  }
//   
//  if (SEG_load_descriptor_from_table(cpu, base, offset, segment) == NULL) {
//    goto error_exit;
//
//  return segment;
//
//  error_exit:
//  return NULL;
//}
//
///*
// * Loads entry from IVT
// * If interrupt vector is greater than limit of IDTR generates #GP exception and returns NULL
// */
//SegmentReg *SEG_load_ivt_entry(CPUx86 *cpu, uint8_t interrupt_vector, SegmentReg *segment) {
//  uint32_t base = cpu->idtr->base_address;
//  uint32_t limit = cpu->idtr->limit;
//  uint32_t offset = interrupt_vector * 4;
//  uint32_t last_offset = offset + 3;
//
//  if (last_offset > limit) {
//   INT_set_interrupt(cpu, INTERRUPT_GP);
//   goto error_exit;
// }
//
//  uint64_t descriptor_phy_addr = PAG_get_physical_addr(cpu, base + offset);
//  segment->base_address = PHYMEM_le_load_word(cpu->phymem, descriptor_phy_addr);
//  segment->selector = PHYMEM_le_load_word(cpu->phymem, descriptor_phy_addr + 2);
//
//  return segment;
//
//  error_exit:
//  return NULL;
//}
//
//
///*
// * Loads descriptor from any desciptor table pointed by
// * table linear address to segment (in 4th arg)   
// * It doesn't check selector and limit!
// * if pointed descriptor (by selector) is not present, it generates #NP exception
// * and returns NULL
// */
//SegmentReg *SEG_load_descriptor_from_table(CPUx86 *cpu, uint32_t table_addr, 
//    uint16_t selector, SegmentReg *segment) {
//  
//  uint64_t descriptor_phy_addr = PAG_get_physical_addr(cpu, table_addr + (uint32_t)(selector & 0xfff8);
//
//  union Descriptor {
//    uint64_t u64;
//    uint8_t u8[8];
//  } descriptor = {PHYMEM_le_load_qword(cpu->phymem, descriptor_phy_addr)};
//
//  union Base_address {
//    uint32_t u32;
//    uint8_t u8[4];
//  } t_base_address = {0};
//
//  union Limit {
//    uint32_t u32;
//    uint8_t u8[4];
//  } t_limit = {0};
//
//  union Access_rights {
//    uint16_t u16;
//    uint8_t u8[2];
//  } t_access_rights = {0};
//
//  union Selector {
//    uint16_t u16;
//    uint8_t u8[2];
//  } t_selector = {selector};
//
//  int variant;
//  t_access_rights.u8[0] = descriptor.u8[5];
//  if (t_access_rights.u16 & SEGMENT_AR_PRESENT) { // Segment Present
//    if (t_access_rights.u16 & SEGMENT_AR_SYSTEM) { // Code/Data Segment
//      variant = 0;
//    }
//    else { // System Segment
//      if (t_access_rights.u16 & SEGMENT_AR_SYSTYPE_GATETYPE) { // Gate Type
//        variant = 1;
//      }
//      else { // System Type
//        variant = 0;
//      }
//    }
//  }
//  else { 
//    INT_set_interrupt(cpu, INTERRUPT_NP);
//    goto error_exit;
//  }
//
//  switch (variant) {
//    case 0: { // Code/Data Segment, System Segment
//      t_base_address.u8[0] = descriptor.u8[2];
//      t_base_address.u8[1] = descriptor.u8[3];
//      t_base_address.u8[2] = descriptor.u8[4];
//      t_base_address.u8[3] = descriptor.u8[7];
//
//      t_limit.u8[0] = descriptor.u8[0];
//      t_limit.u8[1] = descriptor.u8[1];
//      t_limit.u8[2] = descriptor.u8[6] & 0x0f;
//
//      t_access_rights.u8[1] = descriptor.u8[6] & 0xf0;
//      break;
//    }
//    case 1: { // System Gate Type
//      // offset in segment
//      t_base_address.u8[0] = descriptor.u8[0];
//      t_base_address.u8[1] = descriptor.u8[1];
//      t_base_address.u8[2] = descriptor.u8[6];
//      t_base_address.u8[3] = descriptor.u8[7];
//
//      t_selector.u8[0] = descriptor.u8[2];
//      t_selector.u8[1] = descriptor.u8[3];
//
//      t_access_rights.u8[1] = descriptor.u8[4]; // zeros or parametr count for call gate
//      break;
//    }
//  }
//
//  segment->base_address = t_base_address.u32;
//  segment->limit = t_limit.u32;
//  segment->access_rights = t_access_rights.u16;
//  segment->selector = t_selector.u16;
//  return segment;
//
//  error_exit:
//  return NULL;
//}
//
/* 
 * Gets linear address from logical address
 * It can generates #GP, #NP, #SS exceptions
 * 3th argument is code number of segment register from 2sd argument. If segment have
 * If segment have not code number, 3th argument should be 0
 * TODO: It shouldn't check limits!
 */
uint32_t SEG_get_linear_addr(CPUx86 *cpu, SegmentReg *segment, int segment_code, uint32_t logical_offset) {
  uint32_t linear_address = 0;
  
  //if (!SEG_check_limit(segment, logical_offset)) {
  //  if (segment_code == SS) {
  //    INT_set_interrupt(cpu, INTERRUPT_SS);
  //  }
  //  else {
  //    INT_set_interrupt(cpu, INTERRUPT_GP);
  //  }
  //
  //  goto error_exit;
  //}

  switch (cpu->operation_mode) {
    case OPERATION_REAL_MODE: {
      linear_address = segment->selector * 16 + logical_offset;
      break;
    }
    case OPERATION_PROTECTED_MODE: {
      linear_address = segment->base_address + logical_offset;
    }
  }

  return linear_address;

  error_exit:
  return 0;
}








