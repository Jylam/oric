_FDC_command .dsb $310
.dsb _FDC_track   $311
_FDC_sector  .dsb $312
_FDC_data    .dsb $313
_FDC_ready   .dsb $318


_fdc_setup
    lda _FDC_command
    rts
