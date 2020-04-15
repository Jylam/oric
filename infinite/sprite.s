.zero
*= $80
_px             .dsb 1
_py             .dsb 1
tmpsa           .dsb 1
sexel_offset    .dsb 1
pixel           .dsb 1
sy              .dsb 1
_cur_buffer_ptr .dsb 2
y_offset        .dsb 2
sprite          .dsb 2
sprite_alpha    .dsb 2
screen_ptr      .dsb 2
_pdbg           .dsb 2
_sprite_ptrsLOW .dsb 6
_sprite_ptrsHIGH .dsb 6
_sprite_alpha_ptrsLOW .dsb 6
_sprite_alpha_ptrsHIGH .dsb 6


.text
;; void put_sprite(u8 *buf, u8 x, u8 y)
_put_sprite_asm
ldy _py

;; u16 y_offset     = table_y[y];
lda _table_yLOW, y
sta y_offset+0
lda _table_yHIGH, y
sta y_offset+1

;; u8  sexel_offset = table_div6[x];
ldx _px
ldy _table_div6, x
sty sexel_offset

;; u8  pixel   = (x-(table_mul6[sexel_offset]));

lda _table_mul6, y
sta pixel
lda _px
sec
sbc pixel
sta pixel
tay

;; u8  *sprite = (u8*)sprite_ptrs[pixel]; // 16bits pointer to u8*
lda _sprite_ptrsLOW, y
sta sprite
lda _sprite_ptrsHIGH, y
sta sprite+1           ;; 0768 OK


;; u8  *sprite_alpha = (u8*)sprite_alpha_ptrs[pixel];
ldy pixel
lda _sprite_alpha_ptrsLOW, y
sta sprite_alpha
lda _sprite_alpha_ptrsHIGH, y
sta sprite_alpha+1          ;; 0917 OK


;; screen_ptr = buf + y_offset + sexel_offset;
lda _cur_buffer_ptr
clc
adc y_offset
sta screen_ptr
lda _cur_buffer_ptr+1
adc y_offset+1
sta screen_ptr+1   ;; AC80 OK

lda screen_ptr
adc sexel_offset
sta screen_ptr
lda screen_ptr+1
adc #0
sta screen_ptr+1   ;; AC88 OK

lda #$FF  ; So it gets incremented in sprite_line.s to 0
sta sy
;; while(sy<(18*4)) {

#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"
#include "sprite_line.s"

end
rts


