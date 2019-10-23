# Commands #
# make : Generates bin/os
# make run : Generates bin/os and run it with qemu
# make clean: Removes all build files
# make flush : Removes all temporary files
# make asm : Generates the bootloader part (in assembly) named tmp/boot


# Tools #
# Cross Compilers
TOOL_ASM = nasm
TOOL_C = /mnt/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-gcc
TOOL_LINK = /mnt/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-ld

# Flags #
FLAG_ASM = -i src/boot -f bin


.PHONY: run
.PHONY: flush
.PHONY: clean
.PHONY: boot


# OS #
bin/os: bin boot
	cat tmp/bootloader tmp/boot > bin/os

run: bin/os
	qemu-system-i386 -drive format=raw,if=floppy,index=0,file=bin/os


# Source #
# Boot
boot: tmp/boot tmp/bootloader

tmp/bootloader: tmp src/boot/bootloader.asm
	$(TOOL_ASM) $(FLAG_ASM) -o tmp/bootloader src/boot/bootloader.asm

tmp/boot: tmp src/boot/boot.asm
	$(TOOL_ASM) $(FLAG_ASM) -o tmp/boot src/boot/boot.asm


# Directories #
bin:
	mkdir bin

tmp:
	mkdir tmp


# Cleaning #
flush:
	rm -rf tmp

clean: flush
	rm -rf bin
