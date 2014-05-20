__x
.db $0
__y
.db $0
__color
.db $0
__offset
.dw $0
_set_entry_color
    ldy #0      ; Load argument x
    lda (sp),y  ;
    adc #1      ; x++
    sta __x     ; Store X into __x
    ldy #2
    lda (sp),y
    adc #1      ; y++
    sta __y
    ldy #4
    lda (sp),y
    sta __color

    ;offset = (y<<5) + (y<<3);
    lda __y
    asl
    sta __y
    ror
    sta __y+1

    rts
