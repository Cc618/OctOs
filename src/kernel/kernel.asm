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
; --- Interrupts --- ;
; TODO : rm ?
%include "idt.asm"

; Inits the IDT in the idtDescriptor variable
extern idtDescriptor
global loadIDT
loadIDT:
	lidt [idtDescriptor]
	sti

	ret


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


; Outputs a word from a port
; * See documentation in drivers/port.h
global outw
outw:
	push ebp
	mov ebp, esp

	push ax
	push dx

	; dx = port, ax = value
	mov dx, word [ebp + 12]
	mov ax, word [ebp + 8]
	out dx, ax

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

	push dx

	; dx = port, al = value
	mov dx, word [ebp + 8]
	in al, dx

	pop dx

	leave
	ret
