	;
	;bx holds the address of the null-terminated string
	;
print_string:
	pusha
	mov		ah, 0x0e
print_loop:
	mov		al, [bx]
	cmp		al, 0 		;check string ends
	je		return_print_string		;if equal
	int		0x10		;interrupt
	inc		bx			;increase index
	jmp		print_loop
return_print_string:
	popa
	ret

	;
	; prints the value of DX as hex.
	;
print_hex:
	pusha
	mov 	al, 0			;counter
	mov		bx, HEX_OUT		;load template address to bx	
	add		bx, 5			;point to the last byte
	mov		cx, dx			;move the input parameter to cx		
loop_print_hex:
	cmp		al, 4
	je		return_print_hex	;equal
	mov		ah,	cl
	and		ah, 0x0f
	cmp		ah, 9
	jg		is_char	;ah < 9
	add		ah, '0'
	jmp		move_char
is_char:
;	sub		ah, 0xa	
;	add		ah, 'a'
	add		ah, 0x57
move_char:	
	mov		[bx], ah	;write the char to memory
	dec		bx
	inc		al
	shr		cx, 4	
	jmp		loop_print_hex		
return_print_hex:
	mov		bx, HEX_OUT
	call	print_string
	popa
	ret

; global variables
HEX_OUT: 
	db	'0x0000', 0	