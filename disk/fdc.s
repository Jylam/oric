_FDC_command = $310
_FDC_track   = $311
_FDC_sector  = $312
_FDC_data    = $313
_FDC_ready   = $318

__manager_start
_fdc_setup
    lda #$55
    rts

__manager_end

