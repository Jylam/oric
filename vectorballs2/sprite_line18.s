;; Draw 4 bytes (one sprite line)

.(
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#include "sprite_template18.s"
;;        screen_ptr++;
inc screen_ptr
bne END1
inc screen_ptr+1
END1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#include "sprite_template18.s"
;;        screen_ptr++;
inc screen_ptr
bne END2
inc screen_ptr+1
END2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#include "sprite_template18.s"
;;        screen_ptr++;
inc screen_ptr
bne END3
inc screen_ptr+1
END3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#include "sprite_template18.s"
;;        screen_ptr+=37;
lda screen_ptr
adc #37
sta screen_ptr
bcc SOK
inc screen_ptr+1
SOK
.)
