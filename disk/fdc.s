#include "floppy_description.h"
#define CMD_ReadSector	$80
#define CMD_Seek		$1F


_FDC_status  = $310
_FDC_command = $310
_FDC_track   = $311
_FDC_sector  = $312
_FDC_data    = $313
_FDC_ready   = $318

_fdc_setup
    lda #DATA_TRACK  ; Test if we are already on the right track
    cmp _FDC_track
    beq track_ok     ; Yes

                     ; No
    sta _FDC_data    ; Store track# into data register
    lda #CMD_Seek
    sta _FDC_command ; Seek

                     ; Wait for status

track_ok            ; track was the right one





    rts


