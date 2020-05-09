#include "floppy_description.h"
#define CMD_ReadSector	$80
#define CMD_Seek		$1F


_FDC_status  = $310
_FDC_command = $310
_FDC_track   = $311
_FDC_sector  = $312
_FDC_data    = $313
_FDC_flags   = $314
_FDC_ready   = $318

IRQ_save_A .dsb 1
IRQ_save_X .dsb 1
IRQ_save_Y .dsb 1

_fdc_setup
    sei

    lda #<VIA_TIMER_DELAY
    sta $306
    lda #>VIA_TIMER_DELAY
    sta $307



    lda #<_irq_handler
    sta $FFFE
    lda #>_irq_handler
    sta $FFFF
    cli

    lda #DATA_TRACK+1  ; Test if we are already on the right track
    cmp _FDC_track
    beq track_ok     ; Yes

                     ; No
    sta _FDC_data    ; Store track# into data register
    lda #CMD_Seek
    sta _FDC_command ; Seek

                     ; Wait for status

track_ok             ; track was the right one


    rts



_irq_handler
    sta IRQ_save_A
    stx IRQ_save_X
    sty IRQ_save_Y
    rti

