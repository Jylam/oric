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
    IrqOff();

    printf("WHOO\n");
    while(1);
}
