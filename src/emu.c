#include "emu.h"


int main(int argc, char **argv) {
  if (argc != 3) {
    puts("usage: emu <memory size in MB (step 16MB)> <bulid memory>");
    exit(0);
  }

  size_t memory_size = atoll(argv[1]);
  if (memory_size >= 4096) {
    memory_size = 4096;
  }
  else {
    memory_size = ((memory_size + 15) / 16) << 24;
  }

  if (memory_size == 0) {
    return 0;
  }

  char *bulid_memory_file = argv[2];
  size_t bulid_memory_sz;

  FILE* f = open_file(bulid_memory_file, "rb", &bulid_memory_sz);
  uint8_t *bulid_memory_data = malloc(bulid_memory_sz);
  if (bulid_memory_data == NULL) {
    exit(1);
  }

  fread(bulid_memory_data, 1, bulid_memory_sz, f);
  fclose(f);
  bulid_memory_sz = ((uint64_t*)bulid_memory_data)[0];

  //puts("1");
  Emulator emulator;

  emulator.cpu = new_CPUx86();
  //puts("11");
  reset_cpu(emulator.cpu);

  //puts("2");
  emulator.phy_mem = PhysicalMemoryInit(memory_size, bulid_memory_data + 8, bulid_memory_sz);
  free(bulid_memory_data);
  emulator.cpu->phy_mem = emulator.phy_mem;

  printf("GDTR.limit:%x\nCR0:%x\nEAX:%x\nXMM:%x\nCS.base:%x\nEIP:%x\n", 
    emulator.cpu->gdtr->limit, emulator.cpu->creg[CR0], emulator.cpu->gpr[EAX], 
    emulator.cpu->xmm[0].part[0], emulator.cpu->seg[CS].base_address, emulator.cpu->eip);

  //puts("3");
  //printf("%i, %hx\n", bulid_memory_sz, PHYMEM_le_load_word(emulator.phy_mem, 1));

  while (true) {
    cpu_update(emulator.cpu);
    printf("EIP: %x, EAX: %x, ECX: %x\n", emulator.cpu->eip, emulator.cpu->gpr[EAX], emulator.cpu->gpr[ECX]);
  }


  return 0;
}