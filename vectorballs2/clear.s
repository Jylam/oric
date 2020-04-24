;; void clear_sprite(u8 *buf, u8 x, u8 y)

_clear_sprite
ldx _px
ldy _table_div6, x
sty sexel_offset

ldy _py
;; screen_ptr = buf + y_offset + sexel_offset;
lda #<_buffer
clc
adc _table_yLOW, y
sta screen_ptr
lda #>_buffer
adc _table_yHIGH, y
sta screen_ptr+1

lda screen_ptr
adc sexel_offset
sta screen_ptr
bcc OK
inc screen_ptr+1
OK

#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"
#include "clear_template.s"

rts
