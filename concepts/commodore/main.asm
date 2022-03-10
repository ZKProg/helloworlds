;;; Commodore proof of concept

	INCLUDE "./constants.asm"
	PROCESSOR 6502

STATE equ $1500
	
	ORG $1000
	

;;; ---------- INIT SYSTEM --------------------
init_system:
	lda #$00
	sta STATE
	jsr clear_screen
	ldx #$02
	stx BORDER
	stx SCREEN
	jsr init_sprites
	jmp main_loop

init_sprites:
	lda #$01
	sta SPRITE_ENABLED
	lda #$80
	sta SPRITE_0_X
	sta SPRITE_0_Y
	sta SPRITE_0_PTR
	rts
	
;;; ---------- CLEAR SCREEN -------------------
clear_screen:
	lda #$20 		; space char
	ldx #$ff		; counter
loop:	
	sta $0400,x
	sta $0500,x
	sta $0600,x
	sta $0700,x
	dex
	bne loop
	rts

;;; ---------- INPUT CHECKS -------------------
check_fire_1:
	clc
	lda JOY_1
	and #%00010000		; fire
	beq continue
	lda JOY_1
	and #%00000001		; up
	beq playerup
	lda JOY_1
	and #%00000010		; down
	beq playerdown
	lda JOY_1
	and #%00000100		; left
	beq playerleft
	lda JOY_1
	and #%00001000		; right
	beq playerright

	lda #$07
	sta BORDER
	rts
continue:
	lda #$06
	sta BORDER
	rts

;;; ---------- Events -------------------------
playerup:
	lda RASTER_COUNTER
	and #$ff
	bne returnup
	dec SPRITE_0_Y
returnup:	
	rts

playerdown:
	lda RASTER_COUNTER
	and #$ff
	bne returndown
	inc SPRITE_0_Y
returndown:	
	rts


playerleft:
	lda RASTER_COUNTER
	and #$ff
	bne returnleft
	dec SPRITE_0_X
returnleft:	
	rts

playerright:
	lda RASTER_COUNTER
	and #$ff
	bne returnright
	inc SPRITE_0_X
returnright:	
	rts

	
;;; ---------- MAIN LOOP ----------------------
main_loop:
	jsr check_fire_1
	jmp main_loop

;;; ---------- BINARIES -----------------------
	ORG $2000
	INCBIN "./ship.bin"

	
	
	
