;*******************************************************
;	Boot Loader
;*******************************************************
[bits 16]

%include	"./include/macro/descriptor.inc"
%include	"./include/constants.inc"

[org 0x7c00]
	jmp	rm_main

%include	"./include/gdt.inc"
%include	"./include/print_16.inc"
%include	"./include/disk.inc"
;--------------------------------------------------;
;	The main function of real mode
;--------------------------------------------------;
rm_main:
	mov	[BOOT_DRIVE], dl		;get boot drive from dl
	mov	bp, 0x9000				;setup stack
	mov	sp, bp
	
	mov	si, MSG_RM		
	call	print_string

	call	load_kernel			;load kernel

	jmp	switch_to_pm

;-------------------------------------------------;
;	load kernel
;-------------------------------------------------;
load_kernel:			
	pusha
	mov	si, MSG_LOAD_KERNEL
	call	print_string
	;------------------------;
	;	Load kernel from disk.
	;------------------------;
	mov	bx, KERNEL_OFFSET		;set memory offset
	mov	dh, 15					;read 15 sectors
	mov	dl,	[BOOT_DRIVE]		;set drive
	call	disk_load
	popa
	ret
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
	;	jump to kernel code
	;-------------------------------;	
	call	KERNEL_OFFSET
	;-------------------------------;
	;	halt the system
	;-------------------------------;		
	cli
	hlt

%include	"./include/print_32.inc"

; Global variables
BOOT_DRIVE	db 0	
MSG_RM db "Loading operating system...", CR, LF, 0
MSG_LOAD_KERNEL db "Loading Kernel...", CR, LF, 0
MSG_PM db "Successfully witched to protected mode.", 0

times 510-($-$$) db 0
dw 0xaa55	