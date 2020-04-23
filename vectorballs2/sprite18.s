.zero
*= $80
_px             .dsb 1
_py             .dsb 1
sexel_offset    .dsb 1
pixel           .dsb 1
sy              .dsb 1
sprite          .dsb 2
sprite_alpha    .dsb 2
screen_ptr      .dsb 2

.text
;; void put_sprite(u8 *buf, u8 x, u8 y)
_put_sprite_asm

;; u8  sexel_offset = table_div6[x];
ldx _px
ldy _table_div6, x
sty sexel_offset

;; u8  pixel   = (x-(table_mul6[sexel_offset]));

lda _table_mul6, y
sta pixel
txa  ;; _px alrady in X
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



ldy _py
;; screen_ptr = buf + y_offset + sexel_offset;
lda #<_buffer
clc
adc _table_yLOW, y
sta screen_ptr
lda #>_buffer
adc _table_yHIGH, y
sta screen_ptr+1   ;; AC80 OK

lda screen_ptr
adc sexel_offset
sta screen_ptr
bcc OK
inc screen_ptr+1
OK
lda #$FF  ; So it gets incremented in sprite_template.s to 0
sta sy
;; while(sy<(18*4)) {

ldx #0 ;; Used in sprite_template.s
ldy sy ;; y is not modified in sprite_template.s
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
#include "sprite_line18.s"
sty sy ;;

end
rts


