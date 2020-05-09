OSDKPATH=/home/jylam/code/oric/oric/public

CPP=cpp
CFLAGS=-Wall
TOOLS=$OSDKPATH/pc/tools/osdk/main/
AS=$TOOLS/xa/xa
CC=$TOOLS/compiler/compiler
LINKER=$TOOLS/link65/link65
MSPLIT=$TOOLS/macrosplitter/macrosplitter
BIN2TXT=$TOOLS/bin2txt/bin2txt
FILEPACK=$TOOLS/filepack/filepack
PICTCONV=$TOOLS/pictconv/pictconv
LINKLIB=$TOOLS/Osdk/_final_/lib/
OSDKINC=$TOOLS/Osdk/_final_/include/
MACROS=$TOOLS/Osdk/_final_/macro/MACROS.H

BIN=disk

ADDRESS=0xC000

cleanup() {
    rm -f $BIN.final.c .5$BIN.s .$BIN.final.s .0$BIN.s .1$BIN.s .2$BIN.s .3$BIN.s .4$BIN.s .$BIN.linked.s
}
add_c_file() {
    rm -f $BIN.final.c
    cat $1 >> $BIN.final.c
    $CPP -traditional-cpp -I$OSDKINC $BIN.final.c -o .1$BIN.c
	# Remove C comments
	$CPP -xc++ .1$BIN.c -o .2$BIN.c
	# Compile
	$CC -O1 .2$BIN.c .3$BIN.c
	# Apply macros
	cpp -traditional-cpp -include $MACROS .3$BIN.c -o .0$BIN.s -DXA
	cp .0$BIN.s .1$BIN.s
	# Removes #'s
	grep -v '^#' .1$BIN.s > .2$BIN.s
	# Add \n after each assembly instruction
	sed -i 's/\t//g' .2$BIN.s
	sed 's/\:/\n/g' .2$BIN.s > .3$BIN.s
	tr -d '\015' < .3$BIN.s > .4$BIN.s
	tr -d '\011' < .4$BIN.s > .5$BIN.s
	sed -i 's/\r//g' .5$BIN.s
	cat .5$BIN.s >> .$BIN.final.s
}
add_asm_file() {
    cat $1 >> .$BIN.final.s
}

link() {
    $LINKER -d $LINKLIB .$BIN.final.s -o .$BIN.linked.s
}

assemble() {
    $AS .$BIN.linked.s -o $BIN.bin -bt $ADDRESS -C -W -v -l symbols.txt
}

cleanup
~/code/oric/oric/public/pc/tools/osdk/main/FloppyBuilder/FloppyBuilder init floppybuilderscript.txt
add_c_file "main.c"
add_asm_file "sys.s"
add_asm_file "fdc.s"
link
assemble
$TOOLS/header/header -a1 $BIN.bin $BIN.tap $ADDRESS
chmod +x $BIN.tap
$AS -DASSEMBLER=XA sector_1-jasmin.asm -o sector_1-jasmin.o
$AS -DASSEMBLER=XA sector_2-microdisc.asm -o sector_2-microdisc.o -l symbols.tt
$AS -DASSEMBLER=XA sector_3.asm -o sector_3.o
~/code/oric/oric/public/pc/tools/osdk/main/FloppyBuilder/FloppyBuilder build floppybuilderscript.txt
cp test.dsk ~/code/oric/oricutron/disks/

