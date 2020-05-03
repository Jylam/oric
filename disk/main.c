#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

extern void IrqOff(void);

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

void main()
{
    u8 FDC_command = *(u8*)0x310;
    u8 FDC_track   = *(u8*)0x311;
    u8 FDC_sector  = *(u8*)0x312;
    u8 FDC_data    = *(u8*)0x313;
    u8 FDC_ready   = *(u8*)0x318;
    //IrqOff();
    printf("Infos:\n");
    while(1) {
            printf("Command %x\n", FDC_command);
            printf("Track   %x\n", FDC_track);
            printf("Sector  %x\n", FDC_sector);
            printf("Data    %x\n", FDC_data);
            printf("RDY     %x\n", FDC_ready);
    }
    while(1);
}
