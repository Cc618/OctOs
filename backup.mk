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

# Files
SRC = $(wildcard src/kernel/*.c)
OBJ = $(patsubst src/kernel/%.c,tmp/kernel/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

FILE_BOOT = tmp/boot/boot
FILE_BOOTLOADER = tmp/boot/bootloader.o
FILE_KERNEL = tmp/kernel/kernel.o


# Rules #
.PHONY: run
.PHONY: flush
.PHONY: clean
.PHONY: boot
.PHONY: kernel
.PHONY: objects


# OS #
bin/os: bin boot kernel
	cat $(FILE_BOOTLOADER) $(FILE_KERNEL) > bin/os

run: bin/os
	qemu-system-i386 -drive format=raw,if=floppy,index=0,file=bin/os


# Boot #
boot: tmp/boot $(FILE_BOOTLOADER) $(FILE_BOOT)

$(FILE_BOOTLOADER): src/boot/bootloader.asm
	$(TOOL_ASM) $(FLAG_ASM) -f bin -o $@ $<

$(FILE_BOOT): src/boot/boot.asm
	$(TOOL_ASM) $(FLAG_ASM) -f elf -o $@ $<


# Kernel #
# Link all kernel files and the bootloader
kernel: tmp/kernel objects

objects: $(OBJ)
	$(TOOL_LINK) -o $(FILE_KERNEL) -Ttext $(KERNEL_START) $^ --oformat binary

# Each object
tmp/kernel/%.o: src/kernel/%.c
	$(TOOL_C) $(OBJ_FLAGS) $(BUILD_FLAGS) -c -o $@ $<


# Directories #
bin:
	mkdir bin

tmp:
	mkdir tmp

tmp/boot: tmp
	mkdir tmp/boot

tmp/kernel: tmp
	mkdir tmp/kernel


# Cleaning #
flush:
	rm -rf tmp

clean: flush
	rm -rf bin


# Depedencies #
# Include depedencies (auto update headers)
-include $(DEP)
