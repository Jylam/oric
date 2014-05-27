;#define SCREEN $BF68
#define SCREEN $A000

.zero
_zp_start_

px          .db $0
py          .db $0

tx          .db $0
ty          .db $0
tmp_color   .db $0
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
        sta tmp_color
screen_ptr_2
        ; $ffff is modified with the address from table_y
        lda $ffff,y  ; Load screen value
        clc
        ora tmp_color  ; inclusive OR
screen_ptr
        sta $9999,y  ; Store into screen
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
    sta screen_ptr_2+1
    lda screen_ptr+2
    adc #00
    sta screen_ptr+2
    sta screen_ptr_2+2

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
    rts


















; Unrolled. Take x,y arguments, and clears 2*12 bytes
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
    sta screen_ptr_c2+1
    ldy #1
    lda (offset),y
    adc #0
    sta screen_ptr_c+2
    sta screen_ptr_c2+2
    clc



;;;;;;;;;; Start of unrolled loop

    lda #%01000000
    ldy #0
screen_ptr_c
        sta $ffff,y  ; Store into screen
        iny
screen_ptr_c2
        sta $ffff,y  ; Store into screen+1


    ;; Each line we add 40 to the screen pointer
    lda screen_ptr_c+1
    adc #40
    sta screen2_ptr_c+1
    sta screen2_ptr_c2+1
    lda screen_ptr_c+2
    adc #00
    sta screen2_ptr_c+2
    sta screen2_ptr_c2+2


    lda #%01000000
    ldy #0
screen2_ptr_c
        sta $ffff,y  ; Store into screen
        iny
screen2_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen2_ptr_c+1
    adc #40
    sta screen3_ptr_c+1
    sta screen3_ptr_c2+1
    lda screen2_ptr_c+2
    adc #00
    sta screen3_ptr_c+2
    sta screen3_ptr_c2+2
    ; while(ty-- != 0) goto loop_y



    lda #%01000000
    ldy #0
screen3_ptr_c
        sta $ffff,y  ; Store into screen
        iny
screen3_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen3_ptr_c+1
    adc #40
    sta screen4_ptr_c+1
    sta screen4_ptr_c2+1
    lda screen3_ptr_c+2
    adc #00
    sta screen4_ptr_c+2
    sta screen4_ptr_c2+2



    lda #%01000000
    ldy #0
screen4_ptr_c
        sta $ffff,y  ; Store into screen
        iny
screen4_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen4_ptr_c+1
    adc #40
    sta screen5_ptr_c+1
    sta screen5_ptr_c2+1
    lda screen4_ptr_c+2
    adc #00
    sta screen5_ptr_c+2
    sta screen5_ptr_c2+2



    lda #%01000000
    ldy #0
screen5_ptr_c
        sta $ffff,y  ; Store into screen
         iny
screen5_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen4_ptr_c+1
    adc #40
    sta screen6_ptr_c+1
    sta screen6_ptr_c2+1
    lda screen4_ptr_c+2
    adc #00
    sta screen6_ptr_c+2
    sta screen6_ptr_c2+2





    lda #%01000000
    ldy #0
screen6_ptr_c
        sta $ffff,y  ; Store into screen
         iny
screen6_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen6_ptr_c+1
    adc #40
    sta screen7_ptr_c+1
    sta screen7_ptr_c2+1
    lda screen6_ptr_c+2
    adc #00
    sta screen7_ptr_c+2
    sta screen7_ptr_c2+2



    lda #%01000000
    ldy #0
screen7_ptr_c
        sta $ffff,y  ; Store into screen
         iny
screen7_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen7_ptr_c+1
    adc #40
    sta screen8_ptr_c+1
    sta screen8_ptr_c2+1
    lda screen7_ptr_c+2
    adc #00
    sta screen8_ptr_c+2
    sta screen8_ptr_c2+2





    lda #%01000000
    ldy #0
screen8_ptr_c
        sta $ffff,y  ; Store into screen
         iny
screen8_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen8_ptr_c+1
    adc #40
    sta screen9_ptr_c+1
    sta screen9_ptr_c2+1
    lda screen8_ptr_c+2
    adc #00
    sta screen9_ptr_c+2
    sta screen9_ptr_c2+2





    lda #%01000000
    ldy #0
screen9_ptr_c
        sta $ffff,y  ; Store into screen
         iny
screen9_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen9_ptr_c+1
    adc #40
    sta screen10_ptr_c+1
    sta screen10_ptr_c2+1
    lda screen9_ptr_c+2
    adc #00
    sta screen10_ptr_c+2
    sta screen10_ptr_c2+2





    lda #%01000000
    ldy #0
screen10_ptr_c
        sta $ffff,y  ; Store into screen
         iny
screen10_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen10_ptr_c+1
    adc #40
    sta screen11_ptr_c+1
    sta screen11_ptr_c2+1
    lda screen10_ptr_c+2
    adc #00
    sta screen11_ptr_c+2
    sta screen11_ptr_c2+2



    lda #%01000000
    ldy #0
screen11_ptr_c
    sta $ffff,y  ; Store into screen
    iny
screen11_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen11_ptr_c+1
    adc #40
    sta screen12_ptr_c+1
    sta screen12_ptr_c2+1
    lda screen11_ptr_c+2
    adc #00
    sta screen12_ptr_c+2
    sta screen12_ptr_c2+2




    lda #%01000000
    ldy #0
screen12_ptr_c
    sta $ffff,y  ; Store into screen
    iny
screen12_ptr_c2
        sta $ffff,y  ; Store into screen+1

    clc
    ;; Each line we add 40 to the screen pointer
    lda screen12_ptr_c+1
    adc #40
    sta screen13_ptr_c+1
    sta screen13_ptr_c2+1
    lda screen12_ptr_c+2
    adc #00
    sta screen13_ptr_c+2
    sta screen13_ptr_c2+2




    lda #%01000000
    ldy #0
screen13_ptr_c
    sta $ffff,y  ; Store into screen
    iny
screen13_ptr_c2
        sta $ffff,y  ; Store into screen+1


    rts

