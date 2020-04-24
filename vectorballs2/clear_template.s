.(
iny
lda #64
sta (screen_ptr, x)
clc
;;        screen_ptr++;
inc screen_ptr
bne END1
inc screen_ptr+1
END1
iny
lda #64
sta (screen_ptr, x)
clc
;;        screen_ptr++;
inc screen_ptr
bne END2
inc screen_ptr+1
END2
iny
lda #64
sta (screen_ptr, x)
clc
;;        screen_ptr++;
inc screen_ptr
bne END3
inc screen_ptr+1
END3
iny
lda #64
sta (screen_ptr, x)
clc
lda screen_ptr
adc #37
sta screen_ptr
bcc SOK
inc screen_ptr+1
SOK
.)

