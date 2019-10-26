; This file aims to jump to high level code
; It is linked with high level files
; Contains also lowlevel functions

%include "constants.inc"


; Magic word
dw KERNEL_MAGIC

[bits 32]
global entry
extern main

entry:
	; Call the C kernel
	call main

	ret


section .text
; --- Ports --- ;
; Outputs a byte from a port
; * See documentation in drivers/port.h
global outb
outb:
	push ebp
	mov ebp, esp

	push ax
	push dx

	; dx = port, al = value
	mov dx, word [ebp + 12]
	mov al, byte [ebp + 8]
	out dx, al

	pop dx
	pop ax

	leave
	ret

; Receives a byte from a port
; * See documentation in drivers/port.h
global inb
inb:
	push ebp
	mov ebp, esp

	; TODO : rm ?
	xor eax, eax

	push dx

	; dx = port, al = value
	mov dx, word [ebp + 8]
	in al, dx

	pop dx

	leave
	ret
