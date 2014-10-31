;#define SCREEN $BF68
#define SCREEN $A000

.zero
_zp_start_
screen      .dsb 2
stack_pointer .dsb 1
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

    tsx ; Save SP in Y
    txa ; Put X into A
    tay ; Put A into Y

    ldx #$78 ; This place seems unused
    txs ; Set SP to $78

    ; MAGIC
    lda #>(_end_of_clear-1)
    pha
    lda #<(_end_of_clear-1)
    pha

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

_clear_sprite_at_address

    ; Load screen address
    ldy #0      ; Load add_l        2
    lda (sp),y  ;                   5
    tax
    ;sta screen+0 ;                  3
    ldy #2       ;                  2
    lda (sp),y  ; Load add_h        5
    tay
;    sta screen+1;                   3

    txa
    jsr _clear_sprite_at_xy
    rts


#define HEIGHT 12



# Dbug
_draw_sprite_at_xy
    ; Load screen address
    ldy #0      ; Load add_l        2
    lda (sp),y  ;                   5
    tax
    ;sta screen+0 ;                  3
    ldy #2       ;                  2
    lda (sp),y  ; Load add_h        5
    tay
;    sta screen+1;                   3

    txa


        ; x in A, y in Y, we use X for the stack saving
        ; Save old stack pointer
        tsx
        stx stack_pointer

        ; We use X again to set the stack
        ldx #$5E            ;$60 is $78 - 24 elements, the stack is reversed
        txs ; Set SP to x

        ; A contains the x coordinate. Transfer it in X
        tax

        ; Maintenant faut regler le retour. Coller un JMP _end_of_clear

        ; Setup the start of the drawing routine
        lda DrawSpriteJumpTableLow,y
        sta _auto_jsr+1
        lda DrawSpriteJumpTableHigh,y
        sta _auto_jsr+2

        ; Setup the end of the drawing routine
        lda DrawSpriteJumpTableLow+HEIGHT,y
        sta _auto_rts+1
        sta _auto_pla+1
        lda DrawSpriteJumpTableHigh+HEIGHT,y
        sta _auto_rts+2
        sta _auto_pla+2

        lda #$60                ; RTS opcode

_auto_rts
        sta $1234

_auto_jsr
        jmp $1234
_end_of_clear

        lda #$68                ; PLA opcode
_auto_pla
        sta $1234

        ; Restore stack pointer
        ldx stack_pointer
        txs
        rts


savex  .dsb 1

# Dbug
_clear_sprite_at_xy

        ; x in A, y in Y, we use X for the stack saving
        ; Save old stack pointer
        tsx
        stx stack_pointer
        tax

        ; Setup the start of the drawing routine
        lda ClearSpriteJumpTableLow,y
        sta _cauto_jsr+1
        lda ClearSpriteJumpTableHigh,y
        sta _cauto_jsr+2

        ; Setup the end of the drawing routine
        lda ClearSpriteJumpTableLow+HEIGHT,y
        sta _cauto_rts+1
        sta _cauto_pla+1
        lda ClearSpriteJumpTableHigh+HEIGHT,y
        sta _cauto_rts+2
        sta _cauto_pla+2

        lda #$60                ; RTS opcode
_cauto_rts
        sta $1234
        lda #%01000000
_cauto_jsr
        jsr $1234

        lda #$9D                ; STA opcode absolute,X    STA oper,X    9D    3 bytes
_cauto_pla
        sta $1234

        ; Restore stack pointer
        ldx stack_pointer
        txs
        rts








#include "drawsprite.asm"

