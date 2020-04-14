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

lda _table_mul6, y ;; 30 OK
sta pixel
lda _px             ;; 34 OK
sec
sbc pixel
asl            ;; sprite_ptrs holds 16bit values
sta pixel
tay

;; u8  *sprite = (u8*)sprite_ptrs[pixel]; // 16bits pointer to u8*
lda _sprite_ptrs, y
sta sprite
iny
lda _sprite_ptrs, y
sta sprite+1           ;; 0768 OK


;; u8  *sprite_alpha = (u8*)sprite_alpha_ptrs[pixel];
ldy pixel
lda _sprite_alpha_ptrs, y
sta sprite_alpha
iny
lda _sprite_alpha_ptrs, y
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

lda #0
sta sy
;; while(sy<(18*4)) {
y_loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
ldy sy
#include "sprite_template.s"
;;        screen_ptr++;
inc screen_ptr
bne END1
inc screen_ptr+1
END1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

inc sy     ; 5 | 8
ldy sy     ; 3 |
#include "sprite_template.s"
;;        screen_ptr++;
inc screen_ptr
bne END2
inc screen_ptr+1
END2


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

inc sy     ; 5 | 8
ldy sy     ; 3 |
#include "sprite_template.s"
;;        screen_ptr++;
inc screen_ptr
bne END3
inc screen_ptr+1
END3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

inc sy     ; 5 | 8
ldy sy     ; 3 |
#include "sprite_template.s"
;;        screen_ptr+=37;
lda screen_ptr
adc #37
sta screen_ptr
lda screen_ptr+1
adc #0
sta screen_ptr+1



;; if sy>=72, end
inc sy     ; 5 | 8
lda sy     ; 3 |
cmp #72

bcs end
jmp y_loop
end
rts


