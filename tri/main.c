#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

extern void IrqOff(void);
void trifill(u8 x1, u8 y1, u8 x2, u8 y2, u8 x3, u8 y3);

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

u8 table_y[28];

u8 buffer[28*40];

void gen_tables(void) {
    int y;
    double i = 0;
    printf("Please wait ...");
    for(y=0; y<200; y++) {
        table_y[y]  = (y*40)&0x00FF;
    }
    printf("Ok.");
}

void set_colors(void) {
    int y;
    unsigned char mask = 0;
    screen_text[0] = A_BGBLACK;
    screen_text[40] = A_BGBLACK;
    screen_text[80] = A_BGBLACK;

}

void main()
{
	IrqOff();
	gen_tables();
	memset(buffer , 64, 28*40);
	set_colors();
	memcpy(screen, buffer, 28*40);

	trifill(5, 5,
			32, 12,
			15, 26);
	//memcpy(screen, buffer, 28*40);

	for(;;) {
	}
}


void trifill(u8 x1, u8 y1, u8 x2, u8 y2, u8 x3, u8 y3) {
	s8 x, y, xa, xb, xmax, ymax;

	/* Bubble-sort y1 <= y2 <= y3 */
	if(y1 > y2)
	{
		trifill(x2, y2, x1, y1, x3, y3);
		return;
	}

	if(y2 > y3)
	{
		trifill(x1, y1, x3, y3, x2, y2);
		return;
	}

	/* Rasterize our triangle */
	for(y = y1; y <= y3; y++)
	{
		if(y <= y2)
		{
			xa = (y1 == y2) ? x2 : x1 + (x2 - x1) * (y - y1) / (y2 - y1);
			xb = (y1 == y3) ? x3 : x1 + (x3 - x1) * (y - y1) / (y3 - y1);
		}
		else
		{
			xa = (y3 == y2) ? x2 : x3 + (x2 - x3) * (y - y3) / (y2 - y3);
			xb = (y3 == y1) ? x1 : x3 + (x1 - x3) * (y - y3) / (y1 - y3);
		}

		if(xb < xa)
		{
			s8 tmp = xb;
			xb = xa; xa = tmp;
		}

		for(x = xa; x <= xb; x++)
			screen[x+(y*40)] = 'A';
	}
}




