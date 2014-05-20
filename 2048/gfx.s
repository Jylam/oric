__x
.db $0
__y
.db $0
__color
.db $0

_set_entry_color
    ldy #0      ; Load x
    lda (sp),y
    tax
    inx
    stx __x
    ldy #2
    lda (sp),y
    tax
    inx
    stx __y
    ldy #4
    lda (sp),y
    tax
    inx
    stx __color
    rts
