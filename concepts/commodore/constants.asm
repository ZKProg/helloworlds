;;; File holding the constants

BORDER equ $d020
SCREEN equ $d021
SCREEN_MEMORY equ $0400
SCREEN_CONTROL equ $d016
CRAM equ $d800

MEM_BANKING equ $d018	; 1 - 3 => char mem // 4 - 7 => pointer to screen memory
	
SPRITES_COLLISION equ $d01e
SPRITE_BG_COLLISION equ $d01f
SPRITE_DOUBLE equ $d017
SPRITE_ENABLED equ $d015
SPRITE_0_COLOR equ $d027
SPRITE_0_X equ $d000
SPRITE_0_Y equ $d001
SPRITE_0_PTR equ $07f8
	
RASTER_COUNTER equ $d012
INTERRUPT_FLAGS equ $d019
SID equ $d400
TOD equ $dc08

;;; INPUTs
JOY_1 equ $dc01 	; fire = bit 4
JOY_2 equ $dc00
