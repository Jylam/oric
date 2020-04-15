;; Draw 1 byte
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

;; X is zeroed out in sprite.s
and (screen_ptr, x) ;; A contains (sprite_alpha), y
sta (screen_ptr, x)
;;        *screen_ptr |= sprite[sy];
lda (sprite), y

ora (screen_ptr, x) ;; A contains (sprite), y
sta (screen_ptr, x)
jmp ENDSPRITE
FULL
lda (sprite), y
sta (screen_ptr, x)
ENDSPRITE
clc
.)

