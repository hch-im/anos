;*******************************************************
;	Kernel entry function.
;*******************************************************
[bits 32]
;-------------------------------------------------;
;	Declare external symbol 'main'. Linker will 
;	substitute it with the final entrance address
;	of the kernel.
;-------------------------------------------------;	
[extern main]

	;-------------------------------;
	;	jump to kernel code
	;-------------------------------;	
	call	main
	;-------------------------------;
	;	halt the system
	;-------------------------------;		
	cli
	hlt