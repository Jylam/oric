__x
.db $0
__y
.db $0
__color
.db $0

__offset
__offset_l
.db $0
__offset_h
.db $0

_set_entry_color
#if 0
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
#endif
    ;offset = (y<<5) + (y<<3);
    clc
    asl __offset_l   ; y << 5
    rol __offset_h
    asl __offset_l
    rol __offset_h
    asl __offset_l
    rol __offset_h
    asl __offset_l
    rol __offset_h
    asl __offset_l
    rol __offset_h
    clc
    rts
