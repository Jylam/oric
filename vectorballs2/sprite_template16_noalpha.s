;; Draw 1 byte
.(
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
iny
lda (sprite), y
sta (screen_ptr, x)
clc
.)

