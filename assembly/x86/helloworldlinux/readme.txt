How to compile:

nasm -f elf hello.asm
ld -m elf_i386 -s hello.o final
