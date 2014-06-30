;*******************************************************
;	gdt.inc
;	GDT descriptors
;*******************************************************
%ifndef __GDT_INC__
%define __GDT_INC__
[bits 16]
;						Base,	Limit,	Flag1,	Flag2
gdt_start:	Descriptor	0x0,	0x0,	0x0,	0x0		;Dummy descriptor
;-------------------------------------------------------;
;	Code descriptor
;	Flag1:	(present)1 (privilege)00 (descriptor type)1 -> 0x9
;			(code)1 (conforming)0 (readable)1 (accessed)0 -> 0xa
;	Flag2:	(granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 0xc
;-------------------------------------------------------;
gdt_code:	Descriptor	0x0,	0xfffff,	0x9a,	0xc0	
;-------------------------------------------------------;
;	Data descriptor
;	Flag1:	(present)1 (privilege)00 (descriptor type)1 -> 0x9
;			(code)0 (conforming)0 (readable)1 (accessed)0 -> 0x2
;	Flag2:	(granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 0xc
;-------------------------------------------------------;
gdt_data:	Descriptor	0x0,	0xfffff,	0x92,	0xc0	
gdt_end:

gdt_descriptor:
	dw	gdt_end - gdt_start - 1		;size of gdt
	dd	gdt_start					;start address of gdt

CODE_SEG equ gdt_code - gdt_start	;descriptor of code segment	
DATA_SEG equ gdt_data - gdt_start	;descriptor of data segment

%endif ;__GDT_INC__