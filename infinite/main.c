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

volatile u16 table_y[200];
volatile u8  table_mul6[240];
volatile u8  table_div6[240];
volatile u8  table_pixel_value[6];
volatile u8  pos_x_table[256];
volatile u8  pos_y_table[256];

#define HEIGHT 100
#define BUFFER_COUNT 6

u8 buffers[BUFFER_COUNT*HEIGHT*40]; // 7*100*40 -> 28 kbytes

// Precompute Y table (*40) and nibble offsets
void gen_tables(void) {
    int y;
    double i = 0;
    printf("Please wait ...");
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
    for(y=0; y<256; y++) {
        double v = (sin((i/255.0*360.0)*M_PI/180.0)*90.0) + 90;
        pos_x_table[y] = v;
        v = (sin(((i/255.0*360.0)*3.4)*M_PI/180.0)*(HEIGHT/2.5)) + (HEIGHT/2.5);
        pos_y_table[y] = v;
        i+=1.0;
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

void clear_hires(void) {
    memset(screen, 64, 40*200);
}



// 3 * 2 bytes -> 18x16 pixels
void put_sprite(u8 *buf, u8 x, u8 y) {

    u8  *screen_ptr; // Current sexel in the display buffer
    u8  sy = 0;      // sprite current Y
    u16 y_offset     = table_y[y];
    u8  sexel_offset = table_div6[x];

    // Each array is 4*18*6 bytes
    u8  *sprite = &sprite_data[(x-(table_mul6[sexel_offset]))*4*18];
    u8  *sprite_alpha = &sprite_alpha_data[(x-(table_mul6[sexel_offset]))*4*18];

    screen_ptr = buf + y_offset + sexel_offset;

    while(sy<(18*4)) {
        *screen_ptr &= sprite_alpha[sy];
        *screen_ptr |= sprite[sy];
        screen_ptr++;

        *screen_ptr &= sprite_alpha[sy+1];
        *screen_ptr |= sprite[sy+1];
        screen_ptr++;

        *screen_ptr &= sprite_alpha[sy+2];
        *screen_ptr |= sprite[sy+2];
        screen_ptr++;

        *screen_ptr &= sprite_alpha[sy+3];
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
    u8 t = 0;
    u8 *cur_buffer_ptr;
    u8 *screen_ptr;

    gen_tables();
    hires();
    set_colors();

    memset(buffers, 64, BUFFER_COUNT*HEIGHT*40);

    screen_ptr = screen + table_y[((200-HEIGHT)/2)];


    for(;;) {
        x = pos_x_table[t];
        y = pos_y_table[t];
        t++;

        cur_buffer_ptr = &buffers[active_screen*(40*HEIGHT)];
        put_sprite(cur_buffer_ptr, x+20, y);

        memcpy(screen_ptr, cur_buffer_ptr, 40*HEIGHT);

        active_screen++;
        if(active_screen == BUFFER_COUNT)
            active_screen = 0;
    }

}
