# 1 ".3hello_world_simple.c"
# 1 "<built-in>"
# 1 "<command-line>"

# 1 "/usr/include/stdc-predef.h" 1 3 4

# 17 "/usr/include/stdc-predef.h" 3 4











































# 1 "<command-line>" 2
# 1 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H" 1


# 12 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 118 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 127 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 191 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 207 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 252 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 282 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 360 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 4013 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 4072 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"
 
# 4694 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 4793 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/macro/MACROS.H"

# 1 "<command-line>" 2
# 1 ".3hello_world_simple.c"

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
