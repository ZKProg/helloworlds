	section .text

	global _start

_start:
	mov edx, len
	mov ecx, msg
	mov ebx, 1		; 1 for stdout
	mov eax, 4		; syscall for sys_write
	int 0x80		; call kernel

	mov eax, 1		; syscall for sys_exit
	int 0x80

	section .data

	msg db 'Hello ZKProg', 0xA
	len equ $ - msg
	
