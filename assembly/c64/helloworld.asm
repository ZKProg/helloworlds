	processor 6502		; pre processor for dasm

BORDER equ $d020		
SCREEN equ $d021

	org $1000		; start of the program in mem

	lda #$00
	sta BORDER		; load a value into BORDER
	sta SCREEN	

main
	inc BORDER		; increase value stored in BORDER
	inc SCREEN
	jmp main
	
;;; to compile: dasm helloworld.asm -o"final.prg"
;;; to run: x64 final.prg
;;; in x64: SYS 4096
	;; the screen colors should be flickering
