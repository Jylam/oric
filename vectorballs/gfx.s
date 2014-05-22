;#define SCREEN $BF68
#define SCREEN $A00A

.zero
_zp_start_

__x         .db $0
__y         .db $0
__color     .db $0
_tmp1       .dw $0

ty          .db $0

screen      .dsb 2
offset      .dsb 2

_zp_end_
.text

_draw_sprite
    ldy #0      ; Load argument x
    lda (sp),y  ;
    adc #1      ; x++
    sta __x     ; Store x into __x
    ldy #2
    lda (sp),y  ; Load argument y
    adc #1      ; y++
    sta __y
    ldy #4
    lda (sp),y  ; Load argument color
    sta __color


	; for(ty=0;ty<40; ty++) {

    LDA #<SCREEN      ; screen = SCREEN
    STA screen+0
    LDA #>SCREEN
    STA screen+1

    ldy #2       ; screen offset (X, actually)

    lda #255
    sta ty
    ldx ty

loop_y:
    stx ty

    ; screen[offset+2] = color;

    lda #%01010101
    sta (screen),y        ; [_screen+offset+y]
    clc
; }
    ldx ty
    dex
    iny
    bne loop_y
    rts




