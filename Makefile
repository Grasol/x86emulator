all:
	gcc -O3 -Wall -Wextra -march=native -o emu.exe \
 		-I./src/ \
 		-I./src/Memory \
 		-I./src/PrinterLPT \
 		-I./src/CPUx86 \
 		src/emu.c \
 		src/open_file.c \
 		src/Memory/phymem.c \
 		src/PrinterLPT/printer.c \
 		src/CPUx86/cpu.c \
 		src/CPUx86/instr_loader.c \
 		src/CPUx86/instructions_map0.c \
 		src/CPUx86/segmentation.c \
 		src/CPUx86/paging.c \
 		