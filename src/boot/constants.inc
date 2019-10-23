; All constants

; Where to load the kernel (must be a 16 multiple)
%define KERNEL_OFFSET 0x1000

; The address of the stack highest (first) address
%define STACK_HIGH 0xA000

; The magic number we check to verify that the kernel
; is successfully loaded
%define KERNEL_MAGIC 0xCC05


; TODO : Auto set this variable
; How many
%define LOAD_SECTORS_COUNT 1

