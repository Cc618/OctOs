; This file aims to :
; - Load the kernel in memory
; - Switch to 32 bits
; - Call kernel entry

; --- Header --- ;
[org 0x7C00]
[bits 16]

%include "constants.inc"


; --- Boot --- ;
; Main function
_bootloaderMain:
	; - Init - ;
	; Default drive id
	mov byte [defaultDrive], dl

	; - Stack - ;
	; Setup stack
	mov bp, BOOT_STACK_HIGH
	mov sp, bp

	; - Loading - ;
	; Loading kernel...
	mov si, STR_LOAD
	call print

	; Load kernel
	call loadKernel

	; Test if the kernel is loaded
	mov ax, [KERNEL_OFFSET]
	cmp ax, KERNEL_MAGIC
	je .kernel_loaded

	; Error kernel not successfully loaded (incorrect magic number)
	mov si, STR_ERROR_LOAD_CHECK
	call print

	jmp end


	.kernel_loaded:
	; Kernel loaded
	mov si, STR_LOAD_OK
	call print

	; Init 
	call switchPm32

	; ; Check exit code
	; cmp ax, 0
	; je end


	; fatal_error:
	; ; Fatal error
	; mov si, STR_ERROR_FATAL
	; call print
	; jmp $


	end:
	jmp $



; --- Functions --- ;
; Prints with the BIOS the null terminated string pointed by si
; - si : Address of the string to print
; * Adds also a line feed
print:
	push ax

	; For the BIOS print function
	mov ah, 0x0E

	; - Loop - ;
	.loop:
		; Retrieve the char pointed by si in al
		mov al, [si]

		; Break if it's a null char
		cmp al, 0
		je .loop_end

		; Print the char
		int 10h

		inc si

		jmp .loop

	.loop_end:

	; - Line feed (CRLF) - ;
	mov al, 0xD
	int 10h
	mov al, 0xA
	int 10h

	pop ax

	ret


; Loads the kernel
loadKernel:
	pusha

	; Clear carry flag (set to no errors)
	clc

	; - Load kernel - ;
	; Set kernel location (es:bx)
	mov bx, (KERNEL_OFFSET >> 4)
	mov es, bx
	xor bx, bx

	; Set the sectors to read number
	mov al, LOAD_SECTORS_COUNT

	; Cylinder (0)
	xor ch, ch

	; Sector 2 (the boot is the sector 1)
	mov cl, 2

	; Head (0)
	xor dh, dh

	; Drive, same drive as when we have booted
	mov dl, [defaultDrive]

	; Call read function
	mov ah, 0x02
	int 13h

	; - Check errors - ;
	; Carry flag error = can't read
	jnc .noErrorRead

	; Cannot load kernel (read)
	mov si, STR_ERROR_LOAD_READ
	call print
	jmp end

	.noErrorRead:
	; al is the number of sectors read
	cmp al, LOAD_SECTORS_COUNT
	je .noErrorSector

	; Cannot load kernel (load)
	mov si, STR_ERROR_LOAD_SECTORS
	call print
	jmp end

	.noErrorSector:
	popa

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

	; Far jump with the code segment to 32 bits
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
	; Call the kernel main function, just after the magic word
    call (KERNEL_OFFSET + 2)

	; mov word [0xB8000], 0xF043

	; Infinite loop when the kernel leaves
	; TODO : Halt
    jmp $


; --- GDT --- ;
%include "gdt.inc"



; --- Constants --- ;
STR_LOAD: db "Loading kernel...", 0
STR_ERROR_LOAD_READ: db "Error: Cannot load kernel, drive read error", 0
STR_ERROR_LOAD_SECTORS: db "Error: Cannot load kernel, incorrect number of sectors read", 0
STR_ERROR_LOAD_CHECK: db "Error: Kernel not successfully loaded, incorrect magic number", 0
STR_LOAD_OK: db "Kernel loaded", 0
; STR_ERROR_FATAL: db "Error: Fatal, exited with uncommon exit code", 0


; --- Variables --- ;
; The default drive id to read sectors from it
defaultDrive: db 0


; --- Footer --- ;
; Padding
times 510 - ($ - $$) db 0

; Magic number
dw 0xAA55


