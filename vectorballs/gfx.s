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
    ldy #0      ; Load argument x
    lda (sp),y  ;
    sta _x     ; Store x into __x
    ldy #2
    lda (sp),y  ; Load argument y
    sta _y
    ldy #4
    lda (sp),y  ; Load argument color
    sta color

    lda #0
    sta offset+0
    sta offset+1
    ;offset = (y<<5) + (y<<3);  ( *40)
    lda _y
    sta offset+0
    sta offset2+0
    clc
    asl offset+0   ; y << 5
    rol offset+1
    asl offset+0
    rol offset+1
    asl offset+0
    rol offset+1

    lda offset+0   ; we have y<<3 here
    sta offset2+0
    lda offset+1
    sta offset2+1

    asl offset+0
    rol offset+1
    asl offset+0
    rol offset+1   ; and y<<5 here


    clc
    lda offset+0   ; offset+=offset2
    adc offset2+0
    sta offset+0
    lda offset+1
    adc offset2+1
    sta offset+1



    clc
    lda #<SCREEN      ; screen = SCREEN
    adc offset+0
    sta screen+0
    clc
    lda #>SCREEN
    adc offset+1
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




