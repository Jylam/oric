.zero
*= $80
px              .dsb 1
py              .dsb 1
sexel_offset    .dsb 1
pixel           .dsb 1
sy              .dsb 1
y_offset        .dsb 2
sprite          .dsb 2
sprite_alpha    .dsb 2
soffset         .dsb 2
buf             .dsb 2
screen_ptr      .dsb 2

.text
;; void put_sprite(u8 *buf, u8 x, u8 y)
_put_sprite_asm
;; Get *buffer
ldy #0
lda (sp),y
sta buf
iny
lda (sp),y
sta buf+1
iny
;; Get X and Y
lda (sp),y
sta px
iny
iny ;; FIXME compiler pushes that as a 16bit value (??)
lda (sp),y
sta py

;; u16 y_offset     = table_y[y];
asl
tay
lda _table_y, y
sta y_offset+0
iny
lda _table_y, y
sta y_offset+1

;; u8  sexel_offset = table_div6[x];
lda px
tay
lda _table_div6, y
sta sexel_offset

;; u8  pixel   = (x-(table_mul6[sexel_offset]));
tax
lda _table_mul6, x
sta pixel
lda px
sbc pixel
asl            ;; sprite_ptrs holds 16bit values
sta pixel
tay

clc
;; u8  *sprite = (u8*)sprite_ptrs[pixel]; // 16bits pointer to u8*
lda _sprite_ptrs, y
sta sprite
iny
lda _sprite_ptrs, y
sta sprite+1
;; u8  *sprite_alpha = (u8*)sprite_alpha_ptrs[pixel];
lda pixel
tay
lda _sprite_alpha_ptrs, y
sta sprite_alpha
iny
lda _sprite_alpha_ptrs, y
sta sprite_alpha+1


;; screen_ptr = buf + y_offset + sexel_offset;
clc
lda buf
adc y_offset
sta screen_ptr
lda buf+1
adc y_offset+1
sta screen_ptr+1
clc
lda screen_ptr
adc sexel_offset
sta screen_ptr
lda screen_ptr+1
adc sexel_offset+1
sta screen_ptr


;; while(sy<(18*4)) {
;; *screen_ptr &= sprite_alpha[sy];
prout
ldy sy
lda sprite_alpha, y
ldy #0
sta (screen_ptr), y

rts


