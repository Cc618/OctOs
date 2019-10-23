; This file aims to switch to 32 bits and jump to high level code

%include "constants.inc"

[org KERNEL_OFFSET]
[bits 16]

; Magic word
dw KERNEL_MAGIC


_bootMain:

	; No errors
	xor ax, ax

	ret




times 512 - ($ - $$) db 0

