#NO_LIB=1

SRC=main.c sys.s fdc.s
BIN=disk

OBJ=$(SRC:.c=.o)
OBJ+=$(SRC:.s=.o)

include ../public/rules.mk

all: $(SRC) $(BIN)
ddisk:
	~/code/oric/oric/public/pc/tools/osdk/main/FloppyBuilder/FloppyBuilder init floppybuilderscript.txt

	$(AS) -DASSEMBLER=XA sector_1-jasmin.asm -o sector_1-jasmin.o
	$(AS) -DASSEMBLER=XA sector_2-microdisc.asm -o sector_2-microdisc.o
	$(AS) -DASSEMBLER=XA sector_3.asm -o sector_3.o


	~/code/oric/oric/public/pc/tools/osdk/main/FloppyBuilder/FloppyBuilder build floppybuilderscript.txt
	$(AS) -DASSEMBLER=XA sector_1-jasmin.asm -o sector_1-jasmin.o
	$(AS) -DASSEMBLER=XA sector_2-microdisc.asm -o sector_2-microdisc.o -l symbols.tt
	$(AS) -DASSEMBLER=XA sector_3.asm -o sector_3.o
	cp test.dsk ~/code/oric/oricutron/disks/


