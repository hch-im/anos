;*******************************************************
;	Descriptor macro
;	Usage format:	Descriptor	Base, Limit, Flag1, Flag2
;					Base:	dd
;					Limit:	dd	(lower 20 bits)
;					Flag1:	db
;					Flag2:	db	(higher 4 bits)
;*******************************************************
%macro Descriptor 4
	dw	%2 & 0xFFFF								;byte(0-1)	Limit	bits(0-15)
	dw	%1 & 0xFFFF								;byte(2-3)	Base	bits(0-15)
	db	(%1 >> 16) & 0xFF						;byte(4)	Base	bits(16-23)
	db	%3 & 0xFF								;byte(5)	Flag1
	db	((%2 >> 16) & 0x0F) | (%4 & 0xF0)		;byte(6)
												;bits(0-3)	Limit	bits(16-19)
												;bits(4-7)	Flag2	
	db	(%1 >> 24) & 0xFF						;byte(7)	Base	bits(24-31)
%endmacro