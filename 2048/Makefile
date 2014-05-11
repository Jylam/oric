OSDK=/home/jylam/code/oric/public/pc/tools/

CC=$(OSDK)/osdk/main/compiler/compiler
ASM=$(OSDK)/osdk/main/xa/xa
MACROS=$(OSDK)/osdk/main/Osdk/_final_/macro/MACROS.H
HEADER=$(OSDK)/osdk/main/Osdk/_final_/lib/header.s
TAIL=$(OSDK)/osdk/main/Osdk/_final_/lib/tail.s
EUPHORIC_TAPES=/home/jylam/code/oric/emulators/Euphoric/tapes/

all:
	rm -f 2048.asm 2048_preproc.c 2048_preproc 2048.preproc  2048.temp_asm
	$(CC) 2048.c 2048_preproc.c
	cpp -traditional-cpp -include $(MACROS) 2048_preproc.c -o 2048.temp_asm
	grep -v '^#' 2048.temp_asm > 2048.asm
	$(ASM) $(HEADER) 2048.asm $(TAIL) -o 2048.bin
tap:
	wine $(OSDK)/oric/Bin2Tap/Bin/Bin2Tap.exe 2048.bin -o test.tap
	cp test.tap $(EUPHORIC_TAPES)

clean:
	rm -f 2048.asm 2048_preproc.c 2048_preproc 2048.preproc  2048.temp_asm 2048.bin
