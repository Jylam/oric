;#define SCREEN $BF68
#define SCREEN $A000
#define HEIGHT 12

.zero
_zp_start_
screen        .dsb 2
stack_pointer .dsb 1
anim_ptr      .dsb 2
anim_offset   .dsb 2
sprite_count  .dsb 1
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
    ; This address will be poped by the automodified RTS we put in _draw_sprite_at_xy
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





# Dbug
_draw_sprite_at_xy

    ; x in A, y in Y, we use X to backup SP
    ; Save old stack pointer
    tsx
    stx stack_pointer

    ; We use X again to set the stack
    ldx #$5E            ;$60 is $76 - 24 elements, the stack is reversed
    txs ; Set SP to x

    ; A contains the x coordinate. Transfer it in X
    tax

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
#if 0
    ldy #0      ; Load add_l        2
    lda (sp),y  ;                   5
    tax
    ldy #2       ;                  2
    lda (sp),y  ; Load add_h        5
    tay

    txa
#endif
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






_draw_sprites
            ; for(i=0; i<count; i++) {
            ;    draw_sprite_at_xy(anim[offset], anim[offset+1]);
            ;    offset+=2; // X,Y
            ;}

    ; Clear anim_offset (offset in anim_ptr, starting from size, then x y x x y x y ...)
    ldy #0
    sta anim_offset

    ; Load offset, and add it to _anim, put result in anim_ptr
    lda (sp),y  ; Y is alread $0
    clc
    adc #<_anim
    sta anim_ptr

    ldy #1
    lda (sp),y
    adc #>_anim
    clc
    sta anim_ptr+1

    ; Load sprite count in Y
    ldy #0
    lda (anim_ptr),y
    sta sprite_count
    iny
    sty anim_offset

loop_offset
    ; Load anim x in X
    ldy anim_offset
    lda (anim_ptr),y
    tax
    ; Load anim y in Y
    iny
    lda (anim_ptr),y
    ; Save Y as the offset
    iny
    sty anim_offset

    tay

    ; _clear_sprite_at_xy waits for x coordinate in A, y coordinate in Y
    ; and trashes X right away
    txa
    jsr _draw_sprite_at_xy

    lda sprite_count
    cmp anim_offset
    bcs loop_offset

    rts



_clear_sprites
            ; for(i=0; i<count; i++) {
            ;    clear_sprite_at_xy(anim[offset], anim[offset+1]);
            ;    offset+=2; // X,Y,Depth
            ;}

    ; Clear anim_offset (offset in anim_ptr, starting from size, then x y x x y x y ...)
    ldy #0
    sta anim_offset

    ; Load offset, and add it to _anim, put result in anim_ptr
    lda (sp),y  ; Y is alread $0
    clc
    adc #<_anim
    sta anim_ptr

    ldy #1
    lda (sp),y
    adc #>_anim
    clc
    sta anim_ptr+1

    ; Assumes anim_ptr+max(y) stays within page boundary
    ; Load sprite count in Y
    ldy #0
    lda (anim_ptr),y
    sta sprite_count
    iny
    sty anim_offset

c_loop_offset
    ; Load anim x in X
    ldy anim_offset
    lda (anim_ptr),y
    tax
    ; Load anim y in Y
    iny
    lda (anim_ptr),y
    ; Save Y as the offset
    iny
    sty anim_offset

    tay

    ; _clear_sprite_at_xy waits for x coordinate in A, y coordinate in Y
    ; and trashes X right away
    txa
    jsr _clear_sprite_at_xy

    lda sprite_count
    cmp anim_offset
    bcs c_loop_offset

    rts



#include "drawsprite.asm"

