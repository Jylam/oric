#include <lib.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

#include "cube.h"

extern void IrqOff(void);

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

volatile u16  table_y[200];
volatile u8 table_mul6[240];
volatile u8 table_div6[240];
volatile u8 table_pixel_value[6];

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
        table_pixel_value[y] = 1<<(6-(y+1));
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

s16 abs(s16 v) {
    if(v<0) return -v;
    return v;
}

// Hires line, pixel coordinates
void line(u8 x0, u8 y0, u8 x1, u8 y1) {
    // Sexel <- one byte representing six pixels
    // Pixel <- one pixel in a sexel (six of them, then)
    s16 dx = abs(x1-x0);
    s16 dy = abs(y1-y0);
    s8  sx = x0<x1 ? 1 : -1;
    s8  sy = y0<y1 ? 1 : -1;
    s16 err = (dx>dy ? dx : -dy)/2, e2;
    u16 y_offset = table_y[y0];
    u16 old_screen_offset = 0;
    u8  old_sexel = 0;
    u8  sexel_offset = table_div6[x0];

    for(;;) {
        u8  pixel_offset, sexel_save;
        u16 screen_offset;

        screen_offset         = y_offset + sexel_offset;
        sexel_save            = screen[screen_offset];
        pixel_offset          = x0 - table_mul6[sexel_offset];
        old_sexel             = table_pixel_value[pixel_offset] | sexel_save;
        screen[screen_offset] = old_sexel;

        if (x0==x1)
            if (y0==y1) break;

        old_screen_offset     = screen_offset;

        e2 = err;

        if (e2 >-dx) {
            err -= dy;
            x0  += sx;
            sexel_offset = table_div6[x0];
        }
        if (e2 < dy) {
            err += dx;
            y0  += sy;
            y_offset = table_y[y0];
        }
    }
}

u8 cube_edges[] = { 0,1,
                    1,2,
                    2,3,
                    3,0,
                    1,5,
                    5,6,
                    6,2,
                    0,4,
                    4,5,
                    3,7,
                    7,6,
                    7,4};

void main()
{
    u8 test = 0b10000001;
    u16 anim_offset = 0;
    int i;

    gen_tables();
    hires();
    set_colors();

    // Precalc offset into vertices list
    for(i = 0; i < sizeof(cube_edges); i++)
        cube_edges[i] = cube_edges[i]*2;

    for(;;) {
        u8 *c = &cube_anim[anim_offset];
        u8 *edges = cube_edges;

        for(i = 0; i < (sizeof(cube_edges)/2); i++) {
            u8 x0, y0, x1, y1;

            x0 = c[*edges];
            y0 = c[*edges+1];
            edges++;

            x1 = c[*edges];
            y1 = c[*edges+1];
            edges++;

            line(x0, y0, x1, y1);
        }

        anim_offset+=(16); // 16*speed
        if(anim_offset >= sizeof(cube_anim)) {
            anim_offset = 0;
        }
    }

    for(;;) {
        u16 x0 = (rand()%0xDF)+13;
        u16 y0 = rand()%0xBF;
        u16 x1 = (rand()%0xDF)+13;
        u16 y1 = rand()%0xBF;
        line(x0, y0, x1, y1);
    }
}
