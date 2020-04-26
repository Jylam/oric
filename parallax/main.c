#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

extern void IrqOff(void);

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

u8 table_yLOW[200];
u8 table_yHIGH[200];

u8 buffer[200*40];

// Precompute Y table (*40) and nibble offsets
void gen_tables(void) {
    int y;
    double i = 0;
    printf("Please wait ...");
    for(y=0; y<200; y++) {
        table_yLOW[y]  = (y*40)&0x00FF;
        table_yHIGH[y] = ((y*40)&0xFF00)>>8;
    }
}

void set_colors(void) {
    int y;
    unsigned char mask = 0;

    for(y=0; y<200; y++) {
            buffer[(y*40)+1] = A_FWWHITE;
            buffer[(y*40)+0] = A_BGBLACK;

    }

    screen_text[0] = A_BGBLACK;
    screen_text[40] = A_BGBLACK;
    screen_text[80] = A_BGBLACK;

}

void main()
{
    IrqOff();
    gen_tables();
    hires();
    memset(buffer , 64, 200*40);
    set_colors();
    memcpy(screen, buffer, 200*40);


    screen[18] = 0b01001111;
    while(1);
}
