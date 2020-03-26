#include <lib.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

extern void IrqOff(void);

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

volatile u16  table_y[200];
volatile u8 table_mul6[240];
volatile u8 table_div6[240];
volatile u8 table_nibble_offset[6];

// Precompute Y table (*40) and nibble offsets
void gen_tables(void) {
    int y;
    for(y=0; y<200; y++) {
        table_y[y] = y*40;
    }
    for(y=0; y<240; y++) {
        table_div6[y] = y/6;
        table_mul6[y] = y*6;
    }
    for(y=0; y<6; y++) {
        table_nibble_offset[y] = 1<<(6-(y+1));
    }
}

void set_colors(void) {
    int y;
    for(y=0; y<200; y++) {
        screen[(y*40)+0] = A_FWYELLOW;
        screen[(y*40)+1] = A_BGBLACK;
    }

    screen_text[80] = A_FWWHITE;
    screen_text[81] = A_BGBLUE;
}

int abs(int v) {
    if(v<0) return -v;
    return v;
}

void line(int x0, int y0, int x1, int y1) {

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){

        u8  nibble        = table_div6[x0];
        u16 screen_offset = table_y[y0]+nibble;
        u8  nibble_offset = x0 - table_mul6[nibble];
        u8  nibble_save   = screen[screen_offset];

        screen[screen_offset] = table_nibble_offset[nibble_offset] | nibble_save;

        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}


void main()
{
    gen_tables();
    hires();
    set_colors();

    line(15, 10, 50, 180);
    line(15, 50, 170, 20);

}
