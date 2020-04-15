.(
inc sy     ; 5
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
ldy sy
lda (sprite_alpha), y   ; 5
cmp #%01000000          ; 2
beq FULL  ;; Whole byte is to be displayed, don't OR/AND
cmp #%01111111
beq ENDSPRITE ;; Nothing is to be displayed, just quit
sta tmpsa ; 3

ldy #0
lda (screen_ptr), y
and tmpsa
sta (screen_ptr), y
;;        *screen_ptr |= sprite[sy];
ldy sy
lda (sprite), y
sta tmpsa

ldy #0
lda (screen_ptr), y
ora tmpsa
sta (screen_ptr), y
jmp ENDSPRITE

FULL
lda (sprite), y
ldy #0
sta (screen_ptr), y
ENDSPRITE
clc
.)

