;*******************************************************
;	constants
;*******************************************************
%ifndef __CONSTANTS_INC__
%define __CONSTANTS_INC__

CR	equ	0x0d
LF	equ	0x0a

;----------------------;
;	Video memory address
;----------------------;
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

;----------------------;
;	kernel memory offset
;----------------------;
KERNEL_OFFSET equ 0x1000

%endif	;END __CONSTANTS_INC__