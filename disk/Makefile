#NO_LIB=1

SRC=main.c sys.s fdc.s
BIN=disk

OBJ=$(SRC:.c=.o)
OBJ+=$(SRC:.s=.o)

include ../public/rules.mk

all: $(SRC) $(BIN)
ddisk:
	echo LOOOOL
	#~/code/oric/oric/public/pc/tools/osdk/main/tap2dsk/tap2dsk -iCLS:DISK disk.tap 256.tap test.dsk
	#~/code/oric/oric/public/pc/tools/osdk/main/old2mfm/old2mfm test.dsk
	~/code/oric/oric/public/pc/tools/osdk/main/FloppyBuilder/FloppyBuilder init floppybuilderscript.txt

	$(AS) -DASSEMBLER=XA sector_1-jasmin.asm -o sector_1-jasmin.o
	$(AS) -DASSEMBLER=XA sector_2-microdisc.asm -o sector_2-microdisc.o
	$(AS) -DASSEMBLER=XA sector_3.asm -o sector_3.o


	~/code/oric/oric/public/pc/tools/osdk/main/FloppyBuilder/FloppyBuilder build floppybuilderscript.txt
	cp test.dsk ~/code/oric/oricutron/disks/


