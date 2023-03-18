#include "cpu.h"


Instr_list* ILIST_init() {
  size_t sz;
  FILE *f = open_file("instr_list.bin", "rb", &sz);

  char *data = malloc(sz);
  if (!data) {
    goto memory_error;
  }

  fread(data, 1, sz, f);
  fclose(f);

  Instr_list *ilist = malloc(sizeof(Instr_list));
  if (!ilist) {
    goto memory_error;
  }

  ilist->cnt = *((size_t*)data);

  Instr_one *instr = malloc(8 * ilist->cnt);
  if (!instr) {
    goto memory_error;
  }
  ilist->instr = instr;

  for (size_t i = 1; i <= ilist->cnt; ++i) {
    ilist->instr[i].map      = data[i * 8];
    ilist->instr[i].pfx      = data[i * 8 + 1];
    ilist->instr[i].opcode   = data[i * 8 + 2];
    ilist->instr[i].mod      = data[i * 8 + 3];
    ilist->instr[i].nnn      = data[i * 8 + 4];
    ilist->instr[i].rm       = data[i * 8 + 5];
    ilist->instr[i].special  = data[i * 8 + 6];
    ilist->instr[i].opcbits  = data[i * 8 + 7];
  }

  free(data);
  return ilist;

  memory_error:
  fprintf(stderr, "%Memory error\n");
  exit(1);

}


size_t ILIST_get_idx(CPUx86 *cpu, uint8_t map, uint8_t opc, uint8_t pfx, uint8_t mod, uint8_t nnn, uint8_t rm) {
  size_t res = -1;

  Instr_list *ilist = cpu->ilist;
  Instr_one *instr = ilist->instr;
  for (size_t i = 0; i < ilist->cnt; i++) {
    //printf("ILIST: %i %i %i %i", map, opc)
    if (map != instr[i].map) {
      continue;
    }
    
    if (instr[i].opcbits == NULL_ARG) {
      if (opc != instr[i].opcode) {
        continue;
      }
    }
    else {
      uint8_t opc_mask = (0xff << (8 - instr[i].opcbits) & 0xff);
      if ((opc & opc_mask) != instr[i].opcode) {
        continue;
      }
    }
    
    if (pfx != NULL_ARG) {
      if (pfx != instr[i].pfx) {
        continue;
      }
    }
    
    if (mod != NULL_ARG) {
      if (instr[i].mod == 'm') {
        if (mod == 3) {
          continue;
        }
      }
      else if (mod != instr[i].mod) {
        continue;
      }
    }
    
    if (nnn != NULL_ARG) {
      if (nnn != instr[i].nnn) {
        continue;
      }
    }
    
    if (rm != NULL_ARG) {
      if (rm != instr[i].rm) {
        continue;
      }
    }

    res = i;
    break;
  }

  return res;
}
