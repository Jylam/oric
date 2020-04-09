px              .dsb 1
py              .dsb 1
sexel_offset    .dsb 1
pixel           .dsb 1
y_offset        .dsb 2
sprite          .dsb 2
sprite_alpha    .dsb 2
soffset         .dsb 2
buffer          .dsb 2

;; void put_sprite(u8 *buf, u8 x, u8 y)
_put_sprite_asm
;; Get *buffer
ldy #0
lda (sp),y
sta buffer
iny
lda (sp),y
sta buffer+1
iny
;; Get X and Y
lda (sp),y
sta px
iny
lda (sp),y
sta py

;; u16 y_offset     = table_y[y];
tay
lda _table_y, y
sta y_offset

;; u8  sexel_offset = table_div6[x];
lda px
tay
lda _table_div6, y
sta sexel_offset

;; u8  pixel   = (x-(table_mul6[sexel_offset]));
tay
lda _table_mul6, y
sta pixel
lda px
sbc pixel
asl            ;; sprite_ptrs holds 16bit values
sta pixel
tay

;; u8  *sprite = (u8*)sprite_ptrs[pixel]; // 16bits pointer to u8*
lda _sprite_ptrs, y
sta sprite
iny
lda _sprite_ptrs, y
sta sprite+1
;; u8  *sprite_alpha = (u8*)sprite_alpha_ptrs[pixel];
lda pixel
lda _sprite_alpha_ptrs, y
sta sprite_alpha
iny
lda _sprite_alpha_ptrs, y
sta sprite_alpha+1


;; screen_ptr = buf + y_offset + sexel_offset;

rts


