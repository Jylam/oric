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

