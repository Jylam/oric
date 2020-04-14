.(
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


inc sy     ; 5 | 8
.)
