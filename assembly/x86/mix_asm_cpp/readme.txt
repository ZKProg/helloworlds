To compile:

nasm -f elf routine.asm
g++ -c main.cpp

g++ -m32 main.o routine.o -o final 
