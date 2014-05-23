;#define SCREEN $BF68
#define SCREEN $A000

.zero
_zp_start_

_x         .db $0
_y         .db $0
color     .db $0
_tmp1       .dw $0

tx          .db $0

screen      .dsb 2
offset      .dsb 2
offset2      .dsb 2

_zp_end_
.text

_draw_sprite
    sei
    ldy #0      ; Load argument x
    lda (sp),y  ;
    sta _x      ; Store x into _x
    ldy #2
    lda (sp),y  ; Load argument y
    sta _y
    ldy #4
    lda (sp),y  ; Load argument color
    sta color


    ; Set offset to table_y[_y]
    ; table_y is an int, so *2 y
    ; offset2 = y
    ; offset2 <<= 1
    ; offset2 = table_y+offset2

    lda _y
    sta offset2+0
    lda #0
    sta offset2+1
    clc
    asl offset2+0   ; y<<1
    rol offset2+1
    clc
    lda #<(_table_y)  ;offset2 = table_y+(y<<1)
    adc offset2+0
    sta screen+0
    lda #>(_table_y)
    adc offset2+1
    sta screen+1



    ldx #8     ; Width
    stx tx
    ldy _x

loop_x:
    lda color
    sta (screen),y
    clc
    iny
    ldx tx
    clc
    dex
    stx tx
    bne loop_x
    rts




