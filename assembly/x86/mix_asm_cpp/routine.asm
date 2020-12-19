section .text
global sayHello

sayHello:
	mov edx, len
	mov ecx, msg
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov eax, 1
	int 0x80
	ret
	
section .data
	msg db 'Hello from asm routine', 0xA
	len equ $ - msg
