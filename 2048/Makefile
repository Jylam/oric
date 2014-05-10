
CC=~/code/oric/public/pc/tools/osdk/main/compiler/compiler
MACROS=/home/jylam/code/oric/public/pc/tools/osdk/main/Osdk/_final_/macro/MACROS.H
all:
	rm -f 2048_preproc.c 2048_preproc
	$(CC) 2048.c > 2048.preproc
	echo "#include \""$(MACROS)"\"" >> 2048_preproc.c
	cat 2048.preproc >> 2048_preproc.c
	cpp 2048_preproc.c

