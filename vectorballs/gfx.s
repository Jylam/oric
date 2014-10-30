;#define SCREEN $BF68
#define SCREEN $A000

.zero
_zp_start_
screen      .dsb 2

_zp_end_
.text

;;; Wait for VSync
_VSync
    lda $300
vsync_wait
    lda $30D
    and #%00010000 ;test du bit cb1 du registre d'indicateur d'IRQ
    beq vsync_wait
    rts

;;; Disable IRQs
_IrqOff
    sei
    rts


;;; Push _ball 23 first bytes in stack at address $0178
_push_sprite_on_stack
    tsx ; Save SP in x
    txa ; Put X into A
    tay ; Put A into Y

    ldx #$78 ; This place seems unused
    txs ; Set SP to $78

    lda _ball+23
    pha
    lda _ball+22
    pha
    lda _ball+21
    pha
    lda _ball+20
    pha
    lda _ball+19
    pha
    lda _ball+18
    pha
    lda _ball+17
    pha
    lda _ball+16
    pha
    lda _ball+15
    pha
    lda _ball+14
    pha
    lda _ball+13
    pha
    lda _ball+12
    pha
    lda _ball+11
    pha
    lda _ball+10
    pha
    lda _ball+9
    pha
    lda _ball+8
    pha
    lda _ball+7
    pha
    lda _ball+6
    pha
    lda _ball+5
    pha
    lda _ball+4
    pha
    lda _ball+3
    pha
    lda _ball+2
    pha
    lda _ball+1
    pha
    lda _ball
    pha

    tya ; Restore SP
    tax ;
    txs ;

    rts

; Unrolled
; Takes 2 bytes arguments, the 16bits address of the current sprite on the screen
_draw_sprite_at_address

.byt $FF, $FF, $FF
    ; Load screen address
    ldy #0      ; Load add_l        2
    lda (sp),y  ;                   5
    sta screen+0 ;                  3
    ldy #2       ;                  2
    lda (sp),y  ; Load add_h        5
    sta screen+1;                   3

    ; ---------------- Line 0 ----------------
    ; Put the first half
    ; Set SP to the sprite location
    tsx ; Save SP in Y
    txa
    tay

    ldx #$60            ;$60 is $78 - 24 elements, the stack is reversed
    txs ; Set SP to x

    tya ; Put old SP in A
    tax ; Put old SP in X

    pla ; Get pixel value
    ;;;;;;;;;;
    ldy #0
    sta (screen),y ; Store pixel on screen

    ; And the second half
    ldy #1
    pla
    sta (screen),y

    ; ---------------- Line 1 ----------------
    ; Add 40 to
    ; to get to the next line
    clc                                     ; 2
    tya                                     ; 2
    adc #39                                 ; 2
    tay
    ; Put the first half

    pla                                     ; 4
    sta (screen),y
    ; And the second half
    iny                                     ; 2
    pla                                     ; 4
    sta (screen),y                          ; 6
    ; ---------------- Line 2 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    tya
    adc #39
    tay

    ; Pixel value in stack
    pla
    ; Put the first half
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ---------------- Line 3 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ---------------- Line 4 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ---------------- Line 5 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ---------------- Line 6 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y

    ; ----------------------- ----------------
    ; ----------------------- ----------------
    ; Now Y is 240, we need to move screen pointer further
    ; ----------------------- ----------------
    ; ----------------------- ----------------
    clc                    ; 2
    lda screen+0           ; 4
    adc #240               ; 2
    sta screen+0           ; 3
    lda screen+1           ; 4
    adc #0                 ; 2
    sta screen+1           ; 3
    ; ---------------- Line 7 ----------------
    ldy #0
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ----------- END OF LINE 6 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ----------- END OF LINE 7 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ----------- END OF LINE 8 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ----------- END OF LINE 9 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    pla
    sta (screen),y
    ; And the second half
    iny
    pla
    sta (screen),y
    ; ----------- END OF LINE 10 -----------
    txs ; Restore SP
.byt $FF, $FF, $FF
    rts;


_clear_sprite_at_address

    ; Load screen address
    ldy #0      ; Load add_l        2
    lda (sp),y  ;                   5
    sta screen+0 ;                  3
    ldy #2       ;                  2
    lda (sp),y  ; Load add_h        5
    sta screen+1;                   3

    ; ---------------- Line 0 ----------------
    ;;;;;;;;;;
    ldy #0
    lda #%01000000
    sta (screen),y ; Store pixel on screen

    ; And the second half
    ldy #1
    sta (screen),y

    ; ---------------- Line 1 ----------------
    ; Add 40 to
    ; to get to the next line
    clc                                     ; 2
    tya                                     ; 2
    adc #39                                 ; 2
    tay
    ; Put the first half

    lda #%01000000
    sta (screen),y
    ; And the second half
    iny                                     ; 2
    sta (screen),y                          ; 6
    ; ---------------- Line 2 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    tya
    adc #39
    tay

    ; Pixel value in stack
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ---------------- Line 3 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ---------------- Line 4 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ---------------- Line 5 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ---------------- Line 6 ----------------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y

    ; ----------------------- ----------------
    ; ----------------------- ----------------
    ; Now Y is 240, we need to move screen pointer further
    ; ----------------------- ----------------
    ; ----------------------- ----------------
    clc                    ; 2
    lda screen+0           ; 4
    adc #240               ; 2
    sta screen+0           ; 3
    lda screen+1           ; 4
    adc #0                 ; 2
    sta screen+1           ; 3
    ; ---------------- Line 7 ----------------
    ldy #0
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ----------- END OF LINE 6 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ----------- END OF LINE 7 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ----------- END OF LINE 8 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ----------- END OF LINE 9 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    tya
    adc #39
    tay

    ; Address of screen in px:py
    ; Put the first half
    lda #%01000000
    sta (screen),y
    ; And the second half
    iny
    sta (screen),y
    ; ----------- END OF LINE 10 -----------

    rts;











# Dbug
_draw_sprite_at_xy
        ldx #$60            ;$60 is $78 - 24 elements, the stack is reversed
        txs ; Set SP to x
        ldy #5
        ldx #5
        ; Setup the start of the drawing routine
        lda DrawSpriteJumpTableLow,y
        sta _auto_jsr+1
        lda DrawSpriteJumpTableHigh,y
        sta _auto_jsr+2

        ; Setup the end of the drawing routine
        lda DrawSpriteJumpTableLow+12,y
        sta _auto_rts+1
        sta _auto_pla+1
        lda DrawSpriteJumpTableHigh+12,y
        sta _auto_rts+2
        sta _auto_pla+2

        lda #$60                ; RTS opcode
_auto_rts
        sta $1234

_auto_jsr
        jsr $1234

        lda #$68                ; PLA opcode
_auto_pla
        sta $1234
        rts


#include "drawsprite.asm"

