; All constants

; Where to load the kernel (must be a 16 multiple)
%define KERNEL_OFFSET 0x7E00

; The address of the stack highest (first) address
%define KERNEL_STACK_HIGH 0x90000
%define BOOT_STACK_HIGH 0xA000

; The magic number we check to verify that the kernel
; is successfully loaded
%define KERNEL_MAGIC 0xCC05

; The address of the word which describes how many sectors
; we have to read (added after boot.asm compilation)
%define LOAD_SECTORS_OFFSET (0x7C00 + 509)
