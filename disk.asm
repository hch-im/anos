;
; load dh sectors to es:bx from drive dl
;
disk_load:
	push	dx		;store dx to stack		
	mov	ah, 0x02	;BIOS read sector function
	
	mov	al, dh		;Read dh sectors
	mov	ch, 0x00	;select cylinder 0
	mov	dh, 0x00	;select head 0
	mov	cl, 0x02	;start from the 2nd sector, after boot sector. Base is 1.
	
	int	0x13
	
	jc	disk_error	;jump if error

	pop	dx
	cmp	dh, al
	jne	disk_error	;not read all sectors
	ret

disk_error:
	mov	bx, DISK_ERROR_MSG
	call	print_string
	jmp	$

DISK_ERROR_MSG	db	"Disk read error.", 0	
