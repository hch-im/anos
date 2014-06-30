;*******************************************************
;	Boot Loader
;*******************************************************
[bits 16]

%include	"./include/macro/descriptor.inc"
%include	"./include/constants.inc"

[org 0x7c00]
	jmp	rm_main

%include	"./include/gdt.asm"
%include	"./include/print_16.inc"

;--------------------------------------------------;
;	The main function of real mode
;--------------------------------------------------;
rm_main:
	mov	bp, 0x9000				;setup stack
	mov	sp, bp
	
	mov	si, MSG_RM		
	call	print_string

	jmp	switch_to_pm
			
;-------------------------------------------------;
;	switch to protected mode
;	1. switch off interrupts
;	2. load gdt
;	3. set cr0 register
;-------------------------------------------------;
switch_to_pm:
	cli							;switch off interrupts
	lgdt [gdt_descriptor]		;load the base address and limit value of gdt 
								;from memory to GDTR register
	;-------------------------------;
	;	set the first bit of the cr0 
	;	control register to switch on
	;	protected mode.
	;-------------------------------;		
	mov	eax, cr0
	or eax, 0x1
	mov	cr0, eax

	jmp	CODE_SEG:init_pm		;make a far jump to 32-bit code. force CPU to
								;flush its cache of pre-fetched and real-mode
								;decoded instructions.

[bits 32]
;-------------------------------------------------;
;	init protected mode.
;	1. set segment registers
;	2. set stack register
;-------------------------------------------------;
init_pm:
	;-------------------------------;
	;	set segment registers
	;-------------------------------;	
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	;-------------------------------;
	;	update stack register
	;-------------------------------;	
	mov ebp, 0x90000
	mov esp, ebp
	
	call pm_main

pm_main:
	mov esi, MSG_PM
	call print_string_32
	;-------------------------------;
	;	halt the system
	;-------------------------------;		
	cli
	hlt
	
MSG_RM db "Loading operating system ...", CR, LF, 0
MSG_PM db "Protected mode.", 0

%include	"./include/print_32.inc"

times 510-($-$$) db 0
dw 0xaa55	