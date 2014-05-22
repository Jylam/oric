;#define SCREEN $BF68
#define SCREEN $A000

__x
.db $0
__y
.db $0
__color
.db $0


__screen
.dw SCREEN
__tmp1
.dw $0

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
    lda (sp),y  ; Load argument y
    adc #1      ; y++
    sta __y
    ldy #4
    lda (sp),y  ; Load argument color
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

    lda __offset_l   ; offset+=offset2
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

    ldx  #0

    LDA #<SCREEN      ; __screen = SCREEN
    STA __screen+0
    LDA #>SCREEN
    STA __screen+1

    ; screen = screen + offset
    CLC               ; tmp1 is 40 already
    LDA __screen+0
    ADC __offset+0
    STA __screen+0
    LDA __screen+1
    ADC __offset+1
    STA __screen+1



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
    sta __screen,y        ; [_screen+offset+y]
    ; inx

    ; screen+=40;
    CLC               ; tmp1 is 40 already
    LDA __screen+0
    ADC __tmp1+0
    STA __screen+0
    LDA __screen+1
    ADC __tmp1+1
    STA __screen+1
    CLC

   ; }
    ldy ty
    dey
    bne loop_y
    rts




