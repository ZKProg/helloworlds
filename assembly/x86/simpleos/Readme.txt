How to compile:

nasm -f bin -o myfirst.bin myfirst.asm
dd status=noxfer conv=notrunc if=myfirst.bin of=myfirst.flp

How to run on qemu:

qemu-system-i386 -fda myfirst.flp
