;*******************************************************
;	Boot Loader
;	print a null-terminated string in PM mode.
;		esi : holds string address
;	usage:
;		mov	esi, <str addr>
;		call print_string_32	
;*******************************************************
%ifndef __PRINT_32_INC__
%define __PRINT_32_INC__

[bits 32]
print_string_32:
	pusha
	mov	edx, VIDEO_MEMORY
	mov	ah, WHITE_ON_BLACK
print_string_32_loop:
	lodsb
	or	al, al					;al == 0
	jz	return_print_string_32
	
	mov	[edx], ax				;store the char and print attributes to VGA memory
	add	edx, 2					;next cell in VGA memory
	jmp	print_string_32_loop
	
return_print_string_32:
	popa
	ret
	
%endif	;END __PRINT_32_INC__