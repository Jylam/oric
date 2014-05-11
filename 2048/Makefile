OSDK=/home/jylam/code/oric/public/pc/tools/

CC=$(OSDK)/osdk/main/compiler/compiler
ASM=$(OSDK)/osdk/main/xa/xa
MACROS=$(OSDK)/osdk/main/Osdk/_final_/macro/MACROS.H
HEADER=$(OSDK)/osdk/main/Osdk/_final_/lib/header.s
TAIL=$(OSDK)/osdk/main/Osdk/_final_/lib/tail.s
EUPHORIC_TAPES=/home/jylam/code/oric/emulators/Euphoric/tapes/

all:
	rm -f 2048.asm 2048_preproc.c 2048_preproc 2048.preproc 2048.temp_asm 2048_m.asm $(EUPHORIC_TAPES)/test.tap 1.asm
	$(CC) 2048.c 2048_preproc.c
	cpp -traditional-cpp -include $(MACROS) 2048_preproc.c -o 2048.temp_asm
	grep -v '^#' 2048.temp_asm > 2048_m.asm
	$(OSDK)/osdk/main/macrosplitter/macrosplitter 2048_m.asm 2048.asm
	cat $(HEADER) > 1.asm
	cat 2048.asm >> 1.asm
	cat $(TAIL) >>  1.asm
	$(ASM) -bt 0x500 1.asm  -o 2048.bin
tap:
	$(OSDK)/osdk/main/header/header -a1 2048.bin test.tap 0x500
	cp test.tap $(EUPHORIC_TAPES)

clean:
	rm -f 2048.asm 2048_preproc.c 2048_preproc 2048.preproc  2048.temp_asm 2048.bin 2048_m.asm 1.asm
