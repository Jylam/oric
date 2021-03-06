;#define SCREEN $BF68
#define SCREEN $A000

.zero
_zp_start_

__x         .db $0
__y         .db $0
__color     .db $0


screen      .dsb 2
__tmp1      .dsb 2

offset
offset_l  .db $0
offset_h  .db $0
offset2
offset2_l .db $0
offset2_h .db $0

ty          .db $0

_zp_end_
.text


_set_entry_color
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


    ;offset = (y<<5) + (y<<3);
    lda __y
    sta offset_l
    sta offset2_l
    clc
    asl offset_l   ; y << 5
    rol offset_h
    asl offset_l
    rol offset_h
    asl offset_l
    rol offset_h
    asl offset_l
    rol offset_h
    asl offset_l
    rol offset_h

    clc
    asl offset2_l   ; y << 3
    rol offset2_h
    asl offset2_l
    rol offset2_h
    asl offset2_l
    rol offset2_h

    lda offset_l   ; offset+=offset2
    adc offset2_l
    sta offset_l
    lda offset_h
    adc offset2_h
    sta offset_h
    clc

    ; offset+=x
    lda offset_l
    adc __x
    sta offset_l
    lda offset_h
    adc #0           ; Add carry
    sta offset_h
    clc

	; for(ty=0;ty<40; ty++) {

    ldx  #0

    LDA #<SCREEN      ; screen = SCREEN
    STA screen+0
    LDA #>SCREEN
    STA screen+1


    ; screen = screen + offset
    CLC               ; tmp1 is 40 already
    LDA #<screen
    ADC offset+0
    STA screen+0
    LDA #>screen+1
    ADC offset+1
    STA screen+1


    LDA #<40      ; tmp1 = 40
    STA __tmp1+0
    LDA #>40
    STA __tmp1+1

    LDX #2

    lda #40
    sta ty
    ldy ty

loop_y:
    sty ty

    ; screen[offset+2] = color;

    lda #%01010101
    sta (screen),y        ; [_screen+offset+y]

    ; screen+=40;
    CLC               ; tmp1 is 40 already
    LDA screen+0
    ADC __tmp1+0
    STA screen,y
    LDA screen+1
    ADC __tmp1+1
    STA screen+1
    CLC

; }
    ldy ty
    dey
    bne loop_y
    rts




