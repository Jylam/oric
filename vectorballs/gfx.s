;#define SCREEN $BF68
#define SCREEN $A000

.zero
_zp_start_

px          .db $0
py          .db $0

tx          .db $0
ty          .db $0

screen      .dsb 2
offset      .dsb 2

_zp_end_
.text

_draw_sprite
    ldy #0      ; Load argument x
    lda (sp),y  ;
    sta px

    ldy #2
    lda (sp),y  ; Load argument y
    sta py

    ; table_y[y] contains the address of the line y on the screen
    lda py
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
    lda #>_table_y
    adc offset+1
    sta offset+1

    ; Store table_y[offset] into screen_ptr
    clc
    ldy #0
    lda (offset),y
    adc px
    sta screen_ptr+1   ; screen_ptr -> sta $0123,y
    ldy #1
    lda (offset),y
    adc #0
    sta screen_ptr+2

    ; Store sprite address into sprite_ptr
    clc
    lda #<_ball
    sta sprite_ptr+1   ; screen_ptr -> sta $0123,y
    lda #>_ball
    sta sprite_ptr+2


    ldx #12    ; Height
    stx ty
loop_y:
    ldx #2     ; Width
    stx tx
    ldy #0
loop_x:
sprite_ptr
        ; $1234 is modified with the address of sprite+40*y
        lda $1234,y  ; Load sprite byte
screen_ptr
        ; $ffff is modified with the address from table_y
        sta $ffff,y  ; Store into screen
        clc
        iny

        ; loop_x
        ldx tx
        clc
        dex
        stx tx
        bne loop_x

    ;; Each line we add 40 to the screen pointer, $ffff
    clc
    lda screen_ptr+1
    adc #40
    sta screen_ptr+1
    lda screen_ptr+2
    adc #00
    sta screen_ptr+2

    ;; We do the same on the sprite pointer, $1234
    clc
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
break
    rts



















_clear_sprite
    ldy #0      ; Load argument x
    lda (sp),y  ;
    sta px
    ldy #2
    lda (sp),y  ; Load argument y
    sta py

    ; table_y[y] contains the address of the line y on the screen
    lda py
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
    adc px
    sta screen_ptr_c+1   ; screen_ptr -> sta $0123,y
    ldy #1
    lda (offset),y
    adc #0
    sta screen_ptr_c+2
    clc

    ldx #12    ; Height
    stx ty
loop_y_c:
    ldx #2     ; Width
    stx tx
    ldy #0
loop_x_c:
    ; $ffff is modified with the address from table_y
        lda #%01000000
screen_ptr_c
        sta $ffff,y  ; Store into screen
        iny

        ; loop_x
        ldx tx
        clc
        dex
        stx tx
        bne loop_x_c

    ;; Each line we add 40 to the screen pointer
    lda screen_ptr_c+1
    adc #40
    sta screen_ptr_c+1
    lda screen_ptr_c+2
    adc #00
    sta screen_ptr_c+2

    ; while(ty-- != 0) goto loop_y
    clc
    ldx ty
    dex
    stx ty
    bne loop_y_c
    rts

