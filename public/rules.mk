# OSDK rules.mk for GNU Make
# Copyright (c) 2014 Jean-Yves Lamoureux <jylam@lnxscene.org>


# Path of the public/ directory (for instance /home/pennysbird/oric/public/)


OSDKPATH  = /home/jylam/code/oric/oric/public

CPP       = cpp
CFLAGS   += -Wall
TOOLS     =$(OSDKPATH)/pc/tools/osdk/main/
AS        =$(TOOLS)/xa/xa
CC        =$(TOOLS)/compiler/compiler
LINKER    =$(TOOLS)/link65/link65
MSPLIT    =$(TOOLS)/macrosplitter/macrosplitter
BIN2TXT   =$(TOOLS)/bin2txt/bin2txt
FILEPACK  =$(TOOLS)/filepack/filepack
PICTCONV  =$(TOOLS)/pictconv/pictconv
LINKLIB   =$(TOOLS)/Osdk/_final_/lib/
OSDKINC   =$(TOOLS)/Osdk/_final_/include/
MACROS    =$(TOOLS)/Osdk/_final_/macro/MACROS.H
.PHONY: $(DATA) compile_c

ifndef OSDKPATH
$(warning ***)
$(warning **********************************************)
$(warning You must edit)
$(warning $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/rules.mk)
$(warning an fill OSDKPATH)
$(warning **********************************************)
$(error )
endif

RUNBEFOREHACK:=$(shell rm -f $(BIN).final.s $(BIN).final.c)
C_FILES=$(filter %.c, $(SRC))
%.o: %.s
	cat $< >> $(BIN).final.s
%.o: %.c
	cat $< >> $(BIN).final.c

$(BIN): $(DATA) $(OBJ) compile_c
ifneq ($(NO_LINK),1)
	$(LINKER) -d $(LINKLIB) $(BIN).final.s -o .$(BIN).linked.s
else
		cp $(BIN).final.s .$(BIN).linked.s
endif
	$(AS) .$(BIN).linked.s -o $@.bin -bt 0x500 -C -W -v -l symbols.txt
	$(TOOLS)/header/header -a1 $(BIN).bin $(BIN).tap 0x500
	chmod +x $(BIN).tap

compile_c:
ifneq ($(strip $(C_FILES)),)
	$(CPP) -traditional-cpp -I$(OSDKINC) $(BIN).final.c -o .1$(BIN).c
	# Remove C comments
	$(CPP) -xc++ .1$(BIN).c -o .2$(BIN).c
	# Compile
	$(CC) -O1 .2$(BIN).c .3$(BIN).c
	# Apply macros
	cpp -traditional-cpp -include $(MACROS) .3$(BIN).c -o .0$(BIN).s -DXA
	cp .0$(BIN).s .1$(BIN).s
	# Removes #'s
	grep -v '^#' .1$(BIN).s > .2$(BIN).s
	# Add \n after each assembly instruction
	sed -i 's/\t//g' .2$(BIN).s
	sed 's/\:/\n/g' .2$(BIN).s > .3$(BIN).s
	tr -d '\015' < .3$(BIN).s > .4$(BIN).s
	tr -d '\011' < .4$(BIN).s > .5$(BIN).s
	sed -i 's/\r//g' .5$(BIN).s
	cat .5$(BIN).s >> $(BIN).final.s
else
	echo PAS CCCCC
endif
clean::
	rm -f $(BIN) $(DATA) *.tap *.bin symbols.txt .*.c .*.s

