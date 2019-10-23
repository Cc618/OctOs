; This file aims to jump to high level code
; It is linked with high level files

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
