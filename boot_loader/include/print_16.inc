;*******************************************************
;	print_16.inc
;	print a null-terminated string.
;		si : holds string address
;	usage:
;		mov	si, <str addr>
;		call	print_string
;*******************************************************
%ifndef __PRINT_16_INC__
%define __PRINT_16_INC__
[bits 16]

print_string:
	pusha
	mov	ah, 0x0e
print_loop:
	lodsb						;load a byte from [ds:si] or [ds:esi] into al and then 
								;increments or decrements (based on flag) si or esi.
								;lodsw and lodsd works similarly.
	or	al, al					;test if al == 0
	jz	return_print_string		;last is 0
	int	0x10
	jmp	print_loop
	
return_print_string:
	popa
	ret
	
%endif	;END __PRINT_16_INC__
