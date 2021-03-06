# Commands #
# make : Generates bin/os
# make run : Generates bin/os and run it with qemu
# make clean: Removes all build files
# make flush : Removes all temporary files
# make asm : Generates the bootloader part (in assembly) named tmp/boot


# Compilation Pipeline #
# 1. Compile src/boot/boot.asm in binary
# 2. Compile src/kernel/entry.asm as elf (object) file
# 3. Compile C sources as object files
# 4. Link all objects
# 5. Concatenates all files in one binary image (bin/os)


# Constants
# To add debugging symbols
DEBUG ?= 0

# Remove continue to debug before main
DEBUG_GDB_ARGS ?= printf 'target remote localhost:1234\nsymbol-file tmp/kernel/kernel.sym\nb *main\nb *errorHandler\ncontinue\ncontinue\n'

# Either XTERM or GNOME
TERMINAL ?= XTERM

# Whether we want to open the console
# to debug. Use 0 to open it manualy
DEBUG_OPEN_CONSOLE ?= 1

# Tools #
TOOL_ASM ?= nasm
TOOL_PY ?= python3
TOOL_DEBUG ?= gdb
# Cross Compilers
TOOL_CPP ?= /media/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-g++
TOOL_LINK ?= /media/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-ld

# Flags
FLAG_ASM = -i src/boot
FLAG_CPP = -Wall -Wextra -nostdinc -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -lgcc -lk -D__is_kernel -fno-exceptions -fno-rtti -m32 -I src/kernel -MMD -fno-use-cxa-atexit
FLAG_LINK = -T linker.ld -e entry
FLAG_RUN = -drive format=raw,if=floppy,index=0,file=bin/os

# Files
CPP_SRC = $(shell find src/kernel -name "*.cpp")
CPP_OBJ = $(patsubst src/kernel/%.cpp,tmp/kernel/%.o,$(CPP_SRC))
CPP_DEP = $(CPP_OBJ:.o=.d)

# All object files in order to assemble
OBJ = $(FILE_ENTRY) $(CPP_OBJ)

SRC_BOOT = src/boot/boot.asm
SRC_ENTRY = src/kernel/kernel.asm

FILE_BOOT = tmp/boot/boot
FILE_BOOT_SUFFIX = tmp/boot/suffix
FILE_ENTRY = tmp/kernel/kernel.o
FILE_KERNEL = tmp/kernel/kernel


# Debugging #
ifeq ($(DEBUG), 1)
FLAG_CPP += -ggdb
FLAG_RUN += -s -S

DEBUG_COMMAND_EXEC_GDB = cd $(PWD) && (($(DEBUG_GDB_ARGS); cat) | $(TOOL_DEBUG) bin/os); exec bash
endif


# Rules #
.PHONY: run flush clean


# OS #
bin/os: bin $(FILE_BOOT) $(FILE_KERNEL) $(FILE_BOOT_SUFFIX)
	cat $(FILE_BOOT) $(FILE_BOOT_SUFFIX) $(FILE_KERNEL) > bin/os

run: bin/os
ifeq ($(DEBUG), 1)
ifeq ($(DEBUG_OPEN_CONSOLE), 1)
ifeq ($(TERMINAL), GNOME)
	gnome-terminal . -- bash -c "$(DEBUG_COMMAND_EXEC_GDB)"
else ifeq ($(TERMINAL), XTERM)
	xterm -hold -e "$(DEBUG_COMMAND_EXEC_GDB)" &
endif
endif
endif
	qemu-system-i386 $(FLAG_RUN)

# Boot #
$(FILE_BOOT): tmp/boot $(SRC_BOOT) src/boot/constants.inc src/boot/gdt.inc
	$(TOOL_ASM) $(FLAG_ASM) -f bin -o $(FILE_BOOT) $(SRC_BOOT)

$(FILE_BOOT_SUFFIX): $(FILE_KERNEL)
	$(TOOL_PY) utils/boot_suffix.py $(FILE_KERNEL) > $(FILE_BOOT_SUFFIX)


# Kernel #
# Kernel (link objects)
$(FILE_KERNEL): $(OBJ)
ifeq ($(DEBUG), 1)
	$(TOOL_LINK) $(FLAG_LINK) -o tmp/kernel/kernel.elf $^

	objcopy --only-keep-debug tmp/kernel/kernel.elf tmp/kernel/kernel.sym
	objcopy --strip-debug tmp/kernel/kernel.elf
	objcopy -O binary tmp/kernel/kernel.elf $(FILE_KERNEL)
else
	$(TOOL_LINK) $(FLAG_LINK) --oformat binary -o $(FILE_KERNEL) $^
endif

# Kernel Entry (asm)
$(FILE_ENTRY): tmp/kernel $(SRC_ENTRY) src/boot/constants.inc
	$(TOOL_ASM) $(FLAG_ASM) -f elf -o $(FILE_ENTRY) -Isrc/kernel/lowlevel $(SRC_ENTRY)

# C
# TODO : Warning starting address
tmp/kernel/%.o: src/kernel/%.cpp
	mkdir -p $(dir $@)
	$(TOOL_CPP) $(FLAG_CPP) -c -o $@ $<


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
	clear


# Depedencies #
# Include depedencies (auto update headers)
-include $(CPP_DEP)
