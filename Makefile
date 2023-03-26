all:
	gcc -O3 -Wall -Wextra -march=native -o emu.exe \
 		-I./ emu.c open_file.c \
 		-I./Memory Memory/phymem.c \
 		-I./PrinterLPT PrinterLPT/printer.c \
 		-I./CPUx86 CPUx86/cpu.c CPUx86/instr_loader.c CPUx86/instructions_map0.c \
 		CPUx86/segmentation.c CPUx86/paging.c \
 		