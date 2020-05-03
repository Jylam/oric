#NO_LIB=1

SRC=main.c sys.s
BIN=disk

OBJ=$(SRC:.c=.o)
OBJ+=$(SRC:.s=.o)

include ../public/rules.mk

all: $(SRC) $(BIN)
ddisk:
	echo LOOOOL
	~/code/oric/oric/public/pc/tools/osdk/main/tap2dsk/tap2dsk -iCLS:DISK disk.tap test.dsk
	~/code/oric/oric/public/pc/tools/osdk/main/old2mfm/old2mfm test.dsk
	cp test.dsk ~/code/oric/oricutron/disks/


