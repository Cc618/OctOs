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
KERNEL_START = 0x1000

# To add debugging symbols
DEBUG ?= 1

# Tools #
TOOL_ASM ?= nasm
TOOL_PY ?= python3
TOOL_DEBUG ?= gdb
# Cross Compilers
TOOL_CPP ?= /mnt/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-g++
TOOL_LINK ?= /mnt/data/donnees/linux/logiciels/i386-elf-9.1.0/bin/i386-elf-ld

# Flags
FLAG_ASM = -i src/boot
FLAG_C = -Wall -Wextra -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -ffreestanding -m32 -I src/kernel -MMD
FLAG_LINK = -Ttext $(KERNEL_START) --oformat binary -e entry
FLAG_RUN = -drive format=raw,if=floppy,index=0,file=bin/os

# Files
# TODO : CPP
CPP_SRC = $(wildcard src/kernel/*.cpp)
CPP_OBJ = $(patsubst src/kernel/%.cpp,tmp/kernel/%.o,$(CPP_SRC))
CPP_DEP = $(CPP_OBJ:.o=.d)

# All object files in order to assemble
OBJ = $(FILE_ENTRY) $(CPP_OBJ)

SRC_BOOT = src/boot/boot.asm
SRC_ENTRY = src/kernel/entry.asm

FILE_BOOT = tmp/boot/boot
FILE_BOOT_SUFFIX = tmp/boot/suffix
FILE_ENTRY = tmp/kernel/entry.o
FILE_KERNEL = tmp/kernel/kernel


# Debugging #
ifeq ($(DEBUG), 1)
	FLAG_C += -ggdb
	FLAG_RUN += -s -S
endif


# Rules #
.PHONY: run
.PHONY: flush
.PHONY: clean


# OS #
bin/os: bin $(FILE_BOOT) $(FILE_BOOT_SUFFIX) $(FILE_KERNEL)
	cat $(FILE_BOOT) $(FILE_BOOT_SUFFIX) $(FILE_KERNEL) > bin/os

run: bin/os
ifeq ($(DEBUG), 1)
	# TODO : Move
	# objcopy --only-keep-debug bin/os bin/os.sym
	# objcopy --strip-debug bin/os
	# objcopy -O binary bin/os bin/os

	# TODO : Don't continue
	gnome-terminal . -- bash -c "cd $(PWD) && ((printf 'target remote localhost:1234\ncontinue\n'; cat) | $(TOOL_DEBUG) bin/os); exec bash"
	qemu-system-i386 $(FLAG_RUN)
else
	qemu-system-i386 $(FLAG_RUN)
endif

# Boot #
$(FILE_BOOT): tmp/boot $(SRC_BOOT) src/boot/constants.inc src/boot/gdt.inc
	$(TOOL_ASM) $(FLAG_ASM) -f bin -o $(FILE_BOOT) $(SRC_BOOT)

$(FILE_BOOT_SUFFIX): tmp/boot
	$(TOOL_PY) utils/boot_suffix.py $(FILE_BOOT) > $(FILE_BOOT_SUFFIX)


# Kernel #
# Kernel (link objects)
$(FILE_KERNEL): $(OBJ)
	$(TOOL_LINK) $(FLAG_LINK) -o $(FILE_KERNEL) $^

# Entry
$(FILE_ENTRY): tmp/kernel $(SRC_ENTRY) src/boot/constants.inc
	$(TOOL_ASM) $(FLAG_ASM) -f elf -o $(FILE_ENTRY) $(SRC_ENTRY)

# C
# TODO : Recursive directories
# TODO : Warning starting address
tmp/kernel/%.o: src/kernel/%.cpp
	$(TOOL_CPP) $(FLAG_C) -c -o $@ $<


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
-include $(CPP_DEP)
