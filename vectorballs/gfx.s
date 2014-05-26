;#define SCREEN $BF68
#define SCREEN $A000

.zero
_zp_start_

_x          .db $0
_y          .db $0
width       .db $0
height      .db $0
_tmp1       .dw $0

tx          .db $0
ty          .db $0

screen      .dsb 2
offset      .dsb 2

_zp_end_
.text

_draw_sprite
    sei
    ldy #0      ; Load argument x
    lda (sp),y  ;
    sta _x
    ldy #2
    lda (sp),y  ; Load argument y
    sta _y
    ldy #4
    lda (sp),y  ; Load argument width
    sta width
    ldy #6
    lda (sp),y  ; Load argument height
    sta height

    ; table_y[y] contains the address of the line y on the screen
    lda _y
    sta offset+0
    lda #0
    sta offset+1
    clc
    asl offset+0   ; y*2, table_y is a pointer on words
    rol offset+1
    clc

    lda #<_table_y
    adc offset+0
    sta offset+0
    lda #>_table_y ; ; MSB
    adc offset+1
    sta offset+1

    ; Store table_y[offset] into screen_ptr
    ldy #0
    lda (offset),y
    adc _x
    sta screen_ptr+1   ; screen_ptr -> sta $0123,y
    ldy #1
    lda (offset),y
    sta screen_ptr+2
    clc

break
    ; Store sprite address into sprite_ptr
    lda #<_ball
    sta sprite_ptr+1   ; screen_ptr -> sta $0123,y
    lda #>_ball
    sta sprite_ptr+2
    clc


    ldx height    ; Height
    stx ty
loop_y:
    ldx width     ; Width
    stx tx
    ldy #0
loop_x:
    ; $ffff is modified with the address from table_y
sprite_ptr
        lda $1234,y  ; Load sprite byte
screen_ptr
        sta $ffff,y  ; Store into screen
        iny

        ; loop_x
        ldx tx
        clc
        dex
        stx tx
        bne loop_x

    ;; Each line we add 40 to the screen pointer
    lda screen_ptr+1
    adc #40
    sta screen_ptr+1
    lda screen_ptr+2
    adc #00
    sta screen_ptr+2

    ;; We do the same on the sprite pointer
    lda sprite_ptr+1
    adc #40
    sta sprite_ptr+1
    lda sprite_ptr+2
    adc #00
    sta sprite_ptr+2

    ; while(ty-- != 0) goto loop_y
    clc
    ldx ty
    dex
    stx ty
    bne loop_y
    rts

