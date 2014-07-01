;*******************************************************
;	disk.inc
;	load x sectors to memory from drive.
;		dh : specify the number of sectors to load
;		dl : the drive to load from
;		es:bx :	the memory location to load
;	usage:
;		mov dl, <driver>
;		mov dh, <number of sectors>
;		mov	bx, <memory addr>
;		call	disk_load
;*******************************************************
%ifndef __DISK_INC__
%define __DISK_INC__
[bits 16]

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

%endif