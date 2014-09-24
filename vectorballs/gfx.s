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
    ldy #0      ; Load add_l
    lda (sp),y  ;
    sta screen+0
    ldy #2
    lda (sp),y  ; Load add_h
    sta screen+1

    ; Put the first half
    ; Set SP to the sprite location
    tsx ; Save SP in x
    txa ; Put X into A
    tay ; Put A into Y

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

    ; ----------- END OF LINE 0 -----------
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
    ; ----------- END OF LINE 1 -----------
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
    ; ----------- END OF LINE 2 -----------
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
    ; ----------- END OF LINE 3 -----------
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
    ; ----------- END OF LINE 4 -----------
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
    ; ----------- END OF LINE 5 -----------
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
    ; ----------- END OF LINE 6 -----------

    ; Now Y is 240, we need to move screen pointer further
    clc
    lda screen+0
    adc #240
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1
    ldy #0

    ; Address of screen in px:py
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
    rts;


_clear_sprite_at_address
    ldy #0      ; Load add_l
    lda (sp),y  ;
    sta screen+0
    ldy #2
    lda (sp),y  ; Load add_h
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y

    ; ----------- END OF LINE 0 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 1 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 2 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 3 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 4 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 5 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 6 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 7 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 8 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 9 -----------
    ; Add 40 to the screen address
    ; to get to the next line
    clc
    lda screen+0
    adc #40
    sta screen+0
    lda screen+1
    adc #0
    sta screen+1

    ; Address of screen in px:py
    ; Put the first half
    ldy #0
    lda #%01000000
    sta (screen),y
    ; And the second half
    ldy #1
    lda #%01000000
    sta (screen),y
    ; ----------- END OF LINE 10 -----------


    rts;




