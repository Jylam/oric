#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

extern void IrqOff(void);

extern void fdc_setup(void);
extern u8 FDC_command;
extern u8 FDC_track;
extern u8 FDC_sector;
extern u8 FDC_data;
extern u8 FDC_ready;



u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbb80;

void main()
{
    int y;
    IrqOff();
    for(y = 0; y < 28; y++) {
        screen_text[y*40] = A_BGBLUE;
    }

    while(1) {
        y=y+1;
    }
    //fdc_setup();
    printf("Infos:\n");
    printf("Command %x\n", FDC_command);
    printf("Track   %x\n", FDC_track);
    printf("Sector  %x\n", FDC_sector);
    printf("Data    %x\n", FDC_data);
    printf("RDY     %x\n", FDC_ready);
    while(1);
}
