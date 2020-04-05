#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

#include "sprite.h"


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

// Hires line, pixel coordinates, ORed with the current content of the screen
void line(u8 *buf, u8 x0, u8 y0, u8 x1, u8 y1) {
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
        sexel_save            = buf[screen_offset];
        pixel_offset          = x0 - table_mul6[sexel_offset];
        old_sexel             = table_pixel_value[pixel_offset] | sexel_save;
        buf[screen_offset] = old_sexel;

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

void clear_hires(void) {
    memset(screen, 64, 40*200);
}

#define HEIGHT 100
#define BUFFER_COUNT 7

u8 buffers[BUFFER_COUNT*HEIGHT*40]; // 7*100*40 -> 28 kbytes




// 3 * 2 bytes -> 18x16 pixels
void put_sprite(u8 *buf, u8 x, u8 y) {

    u8  *screen_ptr;
    u8  sx = 0, sy = 0; // Sprite X Y
    u16 y_offset     = table_y[y];
    u8  sexel_offset = table_div6[x];
    u8  *sprite;
    switch(x-(sexel_offset*6)) {
        case 0:
            sprite = sprite0;
            break;
        case 1:
            sprite = sprite1;
            break;
        case 2:
            sprite = sprite2;
            break;
        case 3:
            sprite = sprite3;
            break;
        case 4:
            sprite = sprite4;
            break;
        case 5:
            sprite = sprite5;
            break;
    }


    screen_ptr = buf + y_offset + sexel_offset;

    while(sy<(18*4)) {
        *screen_ptr |= sprite[sy];
        screen_ptr++;
        *screen_ptr |= sprite[sy+1];
        screen_ptr++;
        *screen_ptr |= sprite[sy+2];
        screen_ptr++;
        *screen_ptr |= sprite[sy+3];
        screen_ptr += 37;
        sy+=4;
    }
}

void main()
{
    u8 test = 0b10000001;
    u16 anim_offset = 0;
    int x, y;
    u8 active_screen = 0;
    double vx = 0;
    double vy = 0;
    double t = 0;
    u8 *cur_buffer_ptr;
    u8 *screen_ptr;

    gen_tables();
    hires();
    set_colors();

    memset(buffers, 64, BUFFER_COUNT*HEIGHT*40);

    screen_ptr = screen + table_y[((200-HEIGHT)/2)];


    for(;;) {
        cur_buffer_ptr = &buffers[active_screen*(40*HEIGHT)];
        vx = (sin(t*M_PI/180.0)*90.0) + 90;
        x = vx;
        vy = (sin((t*3.4)*M_PI/180.0)*(HEIGHT/2.5)) + (HEIGHT/2.5);
        y = vy;
        //line(cur_buffer_ptr, x+20, y, x+24, y+10);
        //line(cur_buffer_ptr, x+24, y, x+20, y+10);

        put_sprite(cur_buffer_ptr, x+20, y);

        t+=2.1;

        memcpy(screen_ptr, cur_buffer_ptr, 40*HEIGHT);

        active_screen++;
        if(active_screen == BUFFER_COUNT)
            active_screen = 0;
    }

}
