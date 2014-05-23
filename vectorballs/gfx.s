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

_ptr_table_y .dsb 2

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


    ; table_y[y] contains the address of the line y on the screen
    lda _y
    sta offset2+0
    lda #0
    sta offset2+1
    clc
    asl offset2+0   ; y*2, table_y is a word
    rol offset2+1
    clc

    ldy offset2
    lda _table_y, y
    adc offset2+0
    sta screen_ptr+1   ; screen_ptr -> sta $0123,y
    iny
    lda _table_y,y ; ; MSB
    adc offset2+1
    sta screen_ptr+2



    ldx #1     ; Width
    stx tx
    ldy _x

loop_x:
    lda color

    ; $0123 is modified
screen_ptr
    sta $ffff
    clc
    iny
    ldx tx
    clc
    dex
    stx tx
    bne loop_x
    rts




