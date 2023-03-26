#include "emu.h"

argswitch_t switches[ARGP_OPTIONS] = {
    {"--help", "-h", NULL, "show help text and exit", HELP},
    {"--memory_size", "-m", "size", "set maximum size of memory (in MiB)", MEMORY_SIZE},
    {"--memory_dump", "-d", "file", "load binary file to memory", MEMORY_DUMP},
    {"--breakpoint", "-b", "address", "set breakpoint on address", BREAKPOINT_ADDR},
    {"--debug", "-D", NULL, "run emulator in debug mode", DEBUG_MODE}, 
    {"--xchg-breakpoint", "-X", NULL, "xchg ebx, ebx instruction (opcode: 87 DB) switch emulator to debug mode", XCHG_BREAKPOINT}
};


argp_option parse_switch(char *value) {
  if (value[0] != '-') {
    return -1;
  }

  argp_option option = HELP;
  for (int i = 0; i < ARGP_OPTIONS; ++i) {
    bool pared = false;
    if (strcmp(value, switches[i].long_name) == 0) {
      pared = true;
    }
    else if (switches[i].short_name != NULL) {
      if (strcmp(value, switches[i].short_name) == 0) {
        pared = true;
      }
    }

    if (pared) {
      option = switches[i].option;
      break;
    }
  }

  return option;
}

int parse_value(Argp *argp, char *value, argp_option option) {
  int res_arg = 0;
  switch (option) {
    case HELP: {
      argp->help = true;
      break;
    }
    case MEMORY_SIZE: {
      argp->memory_size = atoi(value);
      res_arg = 1;
      break;
    } 
    case MEMORY_DUMP: {
      argp->memory_dump = value;
      res_arg = 1;
      break;
    } 
    case BREAKPOINT_ADDR: {
      if (sscanf(value, "%llx", &(argp->breakpoint_addr)) != 1) {
        argp->help = true;
      }
      else {
        res_arg = 1;
      }

      break;
    } 
    case DEBUG_MODE: {
      argp->debug_mode = true;
      break;
    }
    case XCHG_BREAKPOINT: {
      argp->xchg_breakpoint = true;
      break;
    } 
    default: {
      if (value[0] == '-') {
        argp->help = true;
      }
    }
  }

  return res_arg;
}

void parse_argument(int argc, char **argv, Argp *argp) {  
  enum parser_state {
    SWITCH_PARSE,
    VALUE
  } state = SWITCH_PARSE;

  int i = 0;
  argp_option option = HELP; 
  while (i < argc) {
    switch (state) {
      case SWITCH_PARSE: {
        option = parse_switch(argv[i]);
        ++i;
        if (option == -1) {
          continue;
        }

        state = VALUE;
        break;
      }
      case VALUE: {
        i += parse_value(argp, argv[i], option);
        state = SWITCH_PARSE;
        break;
      }
    }

    if (argp->help) {
      break;
    }
  }

  if ((option == HELP) || (state == VALUE)) {
    puts("Z");
    argp->help = true;
  }
  
  return;
}

void print_help() {
  puts("x86 emulator by Grasol");
  for (int i = 0; i < ARGP_OPTIONS; ++i) {
    int ch = printf(" %s %s", switches[i].short_name, switches[i].long_name);
    if (switches[i].values) {
      ch += printf(" %s", switches[i].values);
    }
    
    char ws[32] = {0};
    memset(ws, ' ', 32 - ch);
    printf("%s", ws);
    
    printf(" : %s\n", switches[i].description);
  }

  return;
}


int main(int argc, char **argv) {
  Argp argp = {0};  
  Emulator emulator = {0};
  
  parse_argument(argc, argv, &argp);

  if (argp.help) {
    print_help();
    exit(0);
  }  

  if (argp.memory_size >= 4096) {
    argp.memory_size = 4096;
  }
  else {
    argp.memory_size = ((argp.memory_size + 15) / 16) << 24; // aligment to 16MB blocks
  }

  if (argp.memory_size == 0) {
    argp.memory_size = 16;
  }

  if (argp.memory_dump) { 
    size_t memory_dump_sz;
    FILE* f = open_file(argp.memory_dump, "rb", &memory_dump_sz);
    uint8_t *memory_dump_data = malloc(memory_dump_sz);
    if (memory_dump_data == NULL) {
      exit(1);
    }

    fread(memory_dump_data, 1, memory_dump_sz, f);
    fclose(f);

    memory_dump_sz = ((uint64_t*)memory_dump_data)[0];
    emulator.phy_mem = PHYMEM_init(argp.memory_size, memory_dump_data + 8, memory_dump_sz);
    free(memory_dump_data);
  }
  else {
    emulator.phy_mem = PHYMEM_init(argp.memory_size, NULL, 0);
  }

  emulator.cpu = CPUx86_init();
  reset_cpu(emulator.cpu);
  emulator.cpu->phy_mem = emulator.phy_mem;

  char printer_name[] = LPT1_PRINTER_NAME;
  emulator.printer = printer_init(&printer_name, LPT1_ADDR, PRINTER_DEFAULT_SIZE_LINE, 
    PRINTER_EMULATOR_WRITE_TIMEOUT, PRINTER_EMULATOR_BUSY_STATE);
  emulator.printer->phy_mem = emulator.phy_mem;

  printf("GDTR.limit:%x\nCR0:%x\nEAX:%x\nXMM:%x\nCS.base:%x\nEIP:%x\n%c\n", 
    emulator.cpu->gdtr->limit, emulator.cpu->creg[CR0], emulator.cpu->gpr[EAX], 
    emulator.cpu->xmm[0].part[0], emulator.cpu->seg[CS].base_address, emulator.cpu->eip, PHYMEM_le_load_byte(emulator.phy_mem, 0xf0040));

  printf("%hx\n", PHYMEM_le_load_word(emulator.phy_mem, 0));

  while (true) {
    cpu_update(emulator.cpu);
    printer_update(emulator.printer);
    printf("EIP: %x, EAX: %x, ECX: %x, EDX: %x, EBX: %x, ESP: %x, EBP: %x, ESI: %x, EDI: %x, EFLAGS: %x\n", emulator.cpu->eip, emulator.cpu->gpr[EAX], emulator.cpu->gpr[ECX], emulator.cpu->gpr[EDX], emulator.cpu->gpr[EBX], 
      emulator.cpu->gpr[ESP], emulator.cpu->gpr[EBP], emulator.cpu->gpr[ESI], emulator.cpu->gpr[EDI], emulator.cpu->eflags);
    printf("DP: %x, SP: %x, CP: %x\n", emulator.printer->data_port, emulator.printer->status_port, emulator.printer->control_port);
    getchar();
  }


  return 0;
}