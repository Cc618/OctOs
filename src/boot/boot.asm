
; ---------------- Header ---------------- ;
[org 0x7C00]
[bits 16]


%define KERNEL_OFFSET 0x1000
%define LOAD_SECTORS_COUNT 1



; ---------------- Boot ---------------- ;
_bootMain:
	; --------- Init -------- ;
	; Default values
	mov byte [defaultDrive], dl

	; --------- Stack -------- ;
	mov bp, 0xA000
	mov sp, bp


	; --------- Loading -------- ;
	mov si, STR_LOAD
	call print

	; Test if the kernel is loaded
	mov ax, [DATA]
	cmp ax, 0xCCCC
	je end

	; Loading failure
	mov si, STR_LOAD_FAILURE
	call print



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


; ---------------- Constants ---------------- ;
STR_LOAD: db "Loading kernel...", 0
STR_LOAD_FAILURE: db "Loading failure", 0
STR_ERROR_LOAD_READ: db "Error: Can't load kernel, drive read error", 0
STR_ERROR_LOAD_SECTORS: db "Error: Can't load kernel, incorrect number of sectors read", 0


; ---------------- Variables ---------------- ;
; The default drive id to read sectors from it
defaultDrive: db 0


; ---------------- Footer ---------------- ;
; Padding
times 510 - ($ - $$) db 0
dw 0xAA55

DATA: dw 0xCCCC


times 1024 - ($ - $$) db 0
