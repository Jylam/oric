 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
ldy sy
iny
sty sy
lda (sprite_alpha), y
sta tmpsa
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
;;        screen_ptr++;
lda screen_ptr
adc #1
sta screen_ptr
lda screen_ptr+1
adc #0
sta screen_ptr+1
clc


