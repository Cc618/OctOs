# Commands #
# make : Generates bin/os
# make run : Generates bin/os and run it with qemu
# make clean: Removes all build files
# make flush : Removes all temporary files
# make asm : Generates the bootloader part (in assembly) named tmp/boot


# Tools #
# Constants
KERNEL_START = 0x1000

# Cross Compilers
TOOL_ASM = nasm
TOOL_C = /mnt/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-gcc
TOOL_LINK = /mnt/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-ld

# Flags
FLAG_ASM = -i src/boot
FLAG_C = -Wall -Wextra -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -ffreestanding -m32 -I src/kernel
FLAG_OBJ = -MMD
FLAG_LINK = -Ttext $(KERNEL_START) --oformat binary -e entry

# Files
SRC = $(wildcard src/kernel/*.c)
# TODO rename C_SRC / C_OBJ...
OBJ = $(patsubst src/kernel/%.c,tmp/kernel/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

SRC_BOOT = src/boot/boot.asm
SRC_ENTRY = src/kernel/entry.asm

FILE_BOOT = tmp/boot/boot
FILE_ENTRY = tmp/kernel/entry.o
FILE_KERNEL = tmp/kernel/kernel


# Rules #
.PHONY: run
.PHONY: flush
.PHONY: clean
# .PHONY: boot
# .PHONY: kernel
# .PHONY: objects


# OS #
bin/os: bin $(FILE_BOOT) $(FILE_KERNEL)
	cat $(FILE_BOOT) $(FILE_KERNEL) > bin/os

run: bin/os
	qemu-system-i386 -drive format=raw,if=floppy,index=0,file=bin/os


# Boot #
$(FILE_BOOT): tmp/boot $(SRC_BOOT)
	$(TOOL_ASM) $(FLAG_ASM) -f bin -o $(FILE_BOOT) $(SRC_BOOT)


# Kernel #
# Kernel (link objects)
# TODO : Create variable for all objects
$(FILE_KERNEL): $(FILE_ENTRY) $(OBJ)
	$(TOOL_LINK) $(FLAG_LINK) -o $(FILE_KERNEL) $^

# Entry
$(FILE_ENTRY): tmp/kernel $(SRC_ENTRY)
	$(TOOL_ASM) $(FLAG_ASM) -f elf -o $(FILE_ENTRY) $(SRC_ENTRY)

# C
# TODO : Recursive directories
# TODO : Warning starting address
tmp/kernel/%.o: src/kernel/%.c
	$(TOOL_C) $(FLAG_C) $(FLAG_OBJ) -c -o $@ $<


# Directories #
bin:
	mkdir -p bin

tmp/boot:
	mkdir -p tmp/boot

tmp/kernel:
	mkdir -p tmp/kernel


# Cleaning #
flush:
	rm -rf tmp

clean: flush
	rm -rf bin


# Depedencies #
# Include depedencies (auto update headers)
-include $(DEP)
