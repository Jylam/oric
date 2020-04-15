.(
inc sy     ; 5
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
ldy sy  ; 3
lda (sprite_alpha), y   ; 5
cmp #%01000000          ; 2
beq FULL  ;; Whole byte is to be displayed, don't OR/AND
cmp #%01111111
beq ENDSPRITE ;; Nothing is to be displayed, just quit

ldy #0
and (screen_ptr), y ;; A contains (sprite_alpha), y
sta (screen_ptr), y
;;        *screen_ptr |= sprite[sy];
ldy sy
lda (sprite), y

ldy #0
ora (screen_ptr), y ;; A contains (sprite), y
sta (screen_ptr), y
jmp ENDSPRITE

FULL
lda (sprite), y
ldy #0
sta (screen_ptr), y
ENDSPRITE
clc
.)

