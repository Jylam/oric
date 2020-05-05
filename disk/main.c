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
u8 *screen_text = (u8*)0xbf68;

void main()
{
#if 0
    u8 FDC_command = *(u8*)0x310;
    u8 FDC_track   = *(u8*)0x311;
    u8 FDC_sector  = *(u8*)0x312;
    u8 FDC_data    = *(u8*)0x313;
    u8 FDC_ready   = *(u8*)0x318;
#endif
    //IrqOff();
    fdc_setup();
    printf("Infos:\n");
    printf("Command %x\n", FDC_command);
    printf("Track   %x\n", FDC_track);
    printf("Sector  %x\n", FDC_sector);
    printf("Data    %x\n", FDC_data);
    printf("RDY     %x\n", FDC_ready);
    while(1);
}
