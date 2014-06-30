[org 0x7c00]
	mov	[BOOT_DRIVE], dl	;BIOS saves boot drive in dl after loading
	
	mov	bp, 0x8000		;set stack to a safe place
	mov	sp, bp

	mov	bx, 0x9000		;load 2 sectors to 0x0000(es):0x9000(bx)
	mov	dh, 2
	mov	dl, [BOOT_DRIVE]	
	call	disk_load

	mov	dx, [0x9000]		;print out the first loaded word
	call	print_hex

	mov	dx, [0x9000 + 512]	;print the first word from the 2nd loaded sector
	call	print_hex
		
	jmp	$

%include	"print.asm"
%include	"disk.asm"

BOOT_DRIVE	db 0
times	510-($-$$) db 0
dw	0xaa55

times	256 dw 0xdada
times	256 dw 0xface
