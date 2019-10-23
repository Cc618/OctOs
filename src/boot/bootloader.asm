; This file aims to load the boot in memory and jump to it

; --- Header --- ;
[org 0x7C00]
[bits 16]

%include "constants.inc" 


; --- Boot --- ;
_bootloaderMain:
	; --------- Init -------- ;
	; Default values
	mov byte [defaultDrive], dl

	; --------- Stack -------- ;
	mov bp, STACK_HIGH
	mov sp, bp

	; --------- Loading -------- ;
	; Loading kernel...
	mov si, STR_LOAD
	call print

	; Load kernel
	call loadKernel

	; Test if the kernel is loaded
	mov ax, [KERNEL_OFFSET]
	cmp ax, KERNEL_MAGIC
	je .kernel_loaded

	; Error kernel not successfully loaded
	mov si, STR_ERROR_LOAD_CHECK
	call print

	jmp $


	.kernel_loaded:
	; Kernel loaded
	mov si, STR_LOAD_OK
	call print

	; Jump to boot (2 bytes later to avoid magic word)
	call KERNEL_OFFSET + 2

	; Check exit code ;
	cmp ax, 0
	je end


	.fatal_error:
	; Fatal error
	mov si, STR_ERROR_FATAL
	call print
	jmp $

	end:
	jmp $



; ---------------- Functions ---------------- ;
;   Prints with the BIOS the null terminated string pointed by si
; * Adds also a line feed
print:
	push ax

	; For the BIOS print function
	mov ah, 0x0E

	; ---- Loop ---- ;
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

	; ---- Line feed (CRLF) ---- ;
	mov al, 0xD
	int 10h
	mov al, 0xA
	int 10h

	pop ax

	ret




;	Loads the kernel
loadKernel:
	pusha

	; Clear carry flag
	clc

	; Set destination to just near the boot location (es:bx)
	mov bx, (KERNEL_OFFSET >> 4)
	mov es, bx
	xor bx, bx

	; Set the sectors to read number
	mov al, LOAD_SECTORS_COUNT

	; Cylinder
	xor ch, ch

	; Sector 2 (the boot is the sector 1)
	mov cl, 2

	; Head
	xor dh, dh

	; Drive
	mov dl, [defaultDrive]

	; Read function
	mov ah, 0x02
	int 13h

	; Check errors
	; Carry flag error = can't read
	jnc .loading_noErrorRead

	mov si, STR_ERROR_LOAD_READ
	call print
	jmp end


	.loading_noErrorRead:
	; al is the number of sectors read
	cmp al, LOAD_SECTORS_COUNT
	je .loading_noErrorSector

	mov si, STR_ERROR_LOAD_SECTORS
	call print
	jmp end

	.loading_noErrorSector:

	popa
	ret


; --- Constants --- ;
STR_LOAD: db "Loading kernel...", 0
STR_ERROR_LOAD_READ: db "Error: Cannot load kernel, drive read error", 0
STR_ERROR_LOAD_SECTORS: db "Error: Cannot load kernel, incorrect number of sectors read", 0
STR_ERROR_LOAD_CHECK: db "Error: Kernel not successfully loaded, incorrect magic number", 0
STR_LOAD_OK: db "Kernel loaded", 0
STR_ERROR_FATAL: db "Error: Fatal, exited with uncommon exit code", 0

; --- Variables --- ;
; The default drive id to read sectors from it
defaultDrive: db 0


; --- Footer --- ;
; Padding
times 510 - ($ - $$) db 0
dw 0xAA55

