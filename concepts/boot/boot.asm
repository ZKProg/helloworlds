	BITS 16


SECTION .TEXT

start:	
	mov ax, 0x07C0
	add ax, 288
	mov ss, ax
	mov sp, 4096

	mov ax, 0x07C0
	mov ds, ax

	mov si, greeting
	call print_string

	jmp $

	greeting db 'ZKPROG boot system', 0		

	
print_string:
	mov ah, 0x0e
repeat:
	lodsb
	cmp al, 0
	je done
	int 10h
	jmp repeat
done:
	ret

SECTION .DATA
	times 510-($-$$) db 0
	dw 0xAA55
	
	

	
	
	
