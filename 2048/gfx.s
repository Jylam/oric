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
__offset2
__offset2_l
.db $0
__offset2_h
.db $0

ty
.db $0

_set_entry_color
    ldy #0      ; Load argument x
    lda (sp),y  ;
    adc #1      ; x++
    sta __x     ; Store x into __x
    ldy #2
    lda (sp),y
    adc #1      ; y++
    sta __y
    ldy #4
    lda (sp),y
    sta __color
    ;offset = (y<<5) + (y<<3);
    lda __y
    sta __offset_l
    sta __offset2_l
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
    asl __offset2_l   ; y << 3
    rol __offset2_h
    asl __offset2_l
    rol __offset2_h
    asl __offset2_l
    rol __offset2_h

    lda __offset_l   ; y<<5 + y<<3
    adc __offset2_l
    sta __offset_l
    lda __offset_h
    adc __offset2_h
    sta __offset_h
    clc

		     ; offset+=x
    lda __offset_l
    adc __x
    sta __offset_l
    lda __offset_h
    adc #0           ; Add carry
    sta __offset_h
    clc

		     ; for(ty=0;ty<40; ty++) {
    lda #40
    sta ty
    ldy ty
loop_y:
    sty ty

		     ;


    ldy ty
    dey
    bne loop_y
    rts




