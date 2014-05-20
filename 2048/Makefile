OSDK=/home/jylam/code/oric/public/pc/tools/
#OSDK=/home/jylam/perso/oric/osdk/public/pc/tools/


CC=$(OSDK)/osdk/main/compiler/compiler
OSDK_INCLUDES=$(OSDK)/osdk/main/Osdk/_final_/include
ASM=$(OSDK)/osdk/main/xa/xa
MACROS=$(OSDK)/osdk/main/Osdk/_final_/macro/MACROS.H
LINKER=$(OSDK)/osdk/main/link65/link65
LINKLIB=$(OSDK)/osdk/main/Osdk/_final_/lib/
HEADER=$(OSDK)/osdk/main/Osdk/_final_/lib/header.s
TAIL=$(OSDK)/osdk/main/Osdk/_final_/lib/tail.s
ORICULATOR_TAPES=/home/jylam/code/oric/emulators/oriculator-read-only/tapes

all:
	rm -f 2048.asm 2048_preproc.c 2048_preproc 2048.preproc 2048.temp_asm 2048_m.asm $(EUPHORIC_TAPES)/test.tap 1.asm go.asm
	cpp -traditional-cpp -I$(OSDK_INCLUDES) 2048.c -o 2048_pre_comment.c
	cpp -xc++ 2048_pre_comment.c -o 2048_pre.c
	$(CC) 2048_pre.c 2048_preproc.c
	cpp -traditional-cpp -include $(MACROS) 2048_preproc.c -o 2048.temp_asm
	grep -v '^#' 2048.temp_asm > 2048_m.asm
	$(OSDK)/osdk/main/macrosplitter/macrosplitter 2048_m.asm 2048.asm
	cat gfx.s >> 2048.asm
	$(LINKER) -d $(LINKLIB) 2048.asm -o go.asm
	$(ASM) -bt 0x500 go.asm  -o 2048.bin
tap:
	$(OSDK)/osdk/main/header/header -a1 2048.bin test.tap 0x500
	cp test.tap $(ORICULATOR_TAPES)
clean:
	rm -f 2048.asm 2048_preproc.c 2048_preproc 2048.preproc  2048.temp_asm 2048.bin 2048_m.asm 1.asm go.asm
