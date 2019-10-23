; This file aims to switch to 32 bits and jump to high level code

; --- Header --- ;
%include "constants.inc"

[org KERNEL_OFFSET]
[bits 16]

; Magic word
dw KERNEL_MAGIC


; --- Main --- ;
_bootMain:
	; - Switch to PM32 - ;
	call switchPm32

	; No errors
	xor ax, ax

	ret


; Procedure to switch to the 32 bits protected mode
switchPm32:
	; Disable interrupts
	cli

	; Load GDT
    lgdt [gdt_descriptor]

	; Set the protected mode bit
    mov eax, cr0
    or eax, 1
    mov cr0, eax

	; Far jump with the code segment
    jmp CODE_SEG:initPm32

	ret


; --- 32 bits Protected Mode --- ;
[bits 32]
; Procedure to init the 32 bits protected mode
initPm32:
	; Set the data segment
	mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	; Update stack base to the top of the free space
    mov ebp, KERNEL_STACK_HIGH
    mov esp, ebp

	; Go to OS' main 32 bits protected mode entry point
    call mainPm32

	ret

; The entry point of the OS in 32 bits protected mode in assembly
; Calls the entry point in high level (C)
mainPm32:
	; Give control to the kernel
    ;;;;; call KERNEL_ENTRY

	mov word [0xB8000], 0xF043

	; Infinite loop when the kernel leaves
	; TODO : Halt
    jmp $


; --- GDT --- ;
%include "gdt.inc"


; --- Footer --- ;
; Padding
times 512 - ($ - $$) db 0
