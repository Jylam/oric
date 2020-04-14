.zero
*= $80
tmpsa           .dsb 1
sexel_offset    .dsb 1
pixel           .dsb 1
sy              .dsb 1
y_offset        .dsb 2
sprite          .dsb 2
sprite_alpha    .dsb 2
buf             .dsb 2
screen_ptr      .dsb 2
_pdbg           .dsb 2

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

ldy _py

;; u16 y_offset     = table_y[y];
lda _table_yLOW, y
sta y_offset+0
lda _table_yHIGH, y
sta y_offset+1

;; u8  sexel_offset = table_div6[x];
ldy _px
lda _table_div6, y
sta sexel_offset

;; u8  pixel   = (x-(table_mul6[sexel_offset]));
tax

lda _table_mul6, x ;; 30 OK
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
lda pixel
tay
lda _sprite_alpha_ptrs, y
sta sprite_alpha
iny
lda _sprite_alpha_ptrs, y
sta sprite_alpha+1          ;; 0917 OK


;; screen_ptr = buf + y_offset + sexel_offset;
lda buf
clc
adc y_offset
sta screen_ptr
lda buf+1
adc y_offset+1
sta screen_ptr+1   ;; AC80 OK

lda screen_ptr
clc
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
lda (sprite_alpha), y
sta tmpsa
ldy #0
lda (screen_ptr), y
and tmpsa
sta (screen_ptr), y
;;        *screen_ptr |= sprite[sy];
ldy sy
lda (sprite), y
sta tmpsa
ldy #0
lda (screen_ptr), y
ora tmpsa
sta (screen_ptr), y
;;        screen_ptr++;
lda screen_ptr
clc
adc #1
sta screen_ptr
lda screen_ptr+1
adc #0
sta screen_ptr+1
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
ldy sy
iny
sty sy
lda (sprite_alpha), y
sta tmpsa
ldy #0
lda (screen_ptr), y
and tmpsa
sta (screen_ptr), y
;;        *screen_ptr |= sprite[sy];
ldy sy
lda (sprite), y
sta tmpsa
ldy #0
lda (screen_ptr), y
ora tmpsa
sta (screen_ptr), y
;;        screen_ptr++;
lda screen_ptr
adc #1
sta screen_ptr
lda screen_ptr+1
adc #0
sta screen_ptr+1

 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
ldy sy
clc
iny
sty sy
lda (sprite_alpha), y
sta tmpsa
ldy #0
lda (screen_ptr), y
and tmpsa
sta (screen_ptr), y
;;        *screen_ptr |= sprite[sy];
ldy sy
lda (sprite), y
sta tmpsa
ldy #0
lda (screen_ptr), y
ora tmpsa
sta (screen_ptr), y
;;        screen_ptr++;
lda screen_ptr
clc
adc #1
sta screen_ptr
lda screen_ptr+1
adc #0
sta screen_ptr+1

 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;        *screen_ptr &= sprite_alpha[sy];
ldy sy
iny
sty sy
lda (sprite_alpha), y
sta tmpsa
ldy #0
lda (screen_ptr), y
and tmpsa
sta (screen_ptr), y
;;        *screen_ptr |= sprite[sy];
ldy sy
lda (sprite), y
sta tmpsa
ldy #0
lda (screen_ptr), y
ora tmpsa
sta (screen_ptr), y
;;        screen_ptr+=37;
lda screen_ptr
adc #37
sta screen_ptr
lda screen_ptr+1
adc #0
sta screen_ptr+1

;; if sy>=72, end
ldy sy
clc
iny
sty sy
tya
cmp #72

bcs end
jmp y_loop
end
rts


