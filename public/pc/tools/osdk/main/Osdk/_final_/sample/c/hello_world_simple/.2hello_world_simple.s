























































 



_main
ldx #6 : lda #0 : jsr enter :
lda #<(L130) : ldy #0 : sta (sp),y : iny : lda #>(L130) : sta (sp),y :
ldy #2 : jsr _printf :
jmp leave :
L130
.byt $48
.byt $65
.byt $6c
.byt $6c
.byt $6f
.byt $20
.byt $57
.byt $6f
.byt $72
.byt $6c
.byt $64
.byt $20
.byt $21
.byt $a
.byt $0
