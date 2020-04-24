.(
ldy #0
lda #64
sta (screen_ptr), y
iny
sta (screen_ptr), y
iny
sta (screen_ptr), y
iny
sta (screen_ptr), y
clc
lda screen_ptr
adc #40
sta screen_ptr
bcc SOK
inc screen_ptr+1
SOK
.)

