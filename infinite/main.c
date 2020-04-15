#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

#include "sprite.h"


extern void IrqOff(void);
extern void put_sprite_asm(); // Uses _px and _py
extern u16  pdbg;

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

volatile u8  table_yLOW[200];
volatile u8  table_yHIGH[200];
volatile u8  table_mul6[240];
volatile u8 sprite_ptrsLOW[6];
volatile u8 sprite_ptrsHIGH[6];
volatile u8 sprite_alpha_ptrsLOW[6];
volatile u8 sprite_alpha_ptrsHIGH[6];
volatile u8  table_div6[240];
volatile u8  table_pixel_value[6];
volatile u8  pos_x_table[256];
volatile u8  pos_y_table[256];
extern u8 *cur_buffer_ptr;
extern u8 px, py;

#define HEIGHT 100
#define BUFFER_COUNT 5

u8 buffers[BUFFER_COUNT*HEIGHT*40]; // 7*100*40 -> 28 kbytes

// Precompute Y table (*40) and nibble offsets
void gen_tables(void) {
    int y;
    double i = 0;
    printf("Please wait ...");
    for(y=0; y<200; y++) {
        table_yLOW[y]  = (y*40)&0x00FF;
        table_yHIGH[y] = ((y*40)&0xFF00)>>8;
    }
    printf("and again ...");
    for(y=0; y<240; y++) {
        table_div6[y] = y/6;
        table_mul6[y] = y*6;
    }
    printf("and again ...");
    for(y=0; y<6; y++) {
        table_pixel_value[y] = 1<<(6-(y+1));
        sprite_ptrsLOW[y] = ((u16) sprite_data +y*4*18)&0x00FF;
        sprite_ptrsHIGH[y] = ((u16) (sprite_data +y*4*18)&0xFF00)>>8;
        sprite_alpha_ptrsLOW[y] = ((u16) sprite_alpha_data +y*4*18)&0x00FF;
        sprite_alpha_ptrsHIGH[y] = ((u16) (sprite_alpha_data +y*4*18)&0xFF00)>>8;
    }
#define ANIM
#ifdef ANIM
    printf("and a last time ...");
    for(y=0; y<256; y++) {
        double v = (sin((i/255.0*360.0)*M_PI/180.0)*90.0) + 90;
        pos_x_table[y] = v;
        v = (cos(((i/255.0*360.0)*3.6)*M_PI/180.0)*(HEIGHT/2.5)) + (HEIGHT/2.5);
        pos_y_table[y] = v;
        i+=1.0;
    }
#endif
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


#if 0
// 3 * 2 bytes -> 18x16 pixels
void put_sprite() {
    u8 x = px, y = py;
    u8  *screen_ptr; // Current sexel in the display buffer
    u8  sy = 0;      // sprite current Y
    u16 y_offset     = (table_yHIGH[y]<<8)|table_yLOW[y];
    u8  sexel_offset = table_div6[x];


    // Each array is 4*18*6 bytes
    u8  pixel   = (x-(table_mul6[sexel_offset]));

    u8  *sprite = (u8*)sprite_ptrs[pixel];
    u8  *sprite_alpha = (u8*)sprite_alpha_ptrs[pixel];

    screen_ptr = cur_buffer_ptr + y_offset + sexel_offset;

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
#endif
void sleep(int t) {
    int i = 0;
    for(i = 0; i < t; i++) {
        printf("Wait %d\n", i);
    }
}
void main()
{
    u8 test = 0b10000001;
    u16 anim_offset = 0;
    u8 x, y;
    u8 active_screen = 0;
    u8 t = 0;
    u8 *screen_ptr;
    u16 y_offset = 0;
    gen_tables();
    IrqOff();
    hires();
    set_colors();

    memset(buffers, 64, BUFFER_COUNT*HEIGHT*40);

    y_offset = (table_yHIGH[((200-HEIGHT)/2)]<<8)|(table_yLOW[((200-HEIGHT)/2)]);
    screen_ptr = screen + y_offset;

    //cur_buffer_ptr = screen_ptr;
    cur_buffer_ptr = screen;
    x = 52;
    y = 30;
    //put_sprite    (cur_buffer_ptr, x, y);
#ifndef ANIM
    for(py=0;  py<182; py+=18)
    for(px=18; px<222; px+=18)
      put_sprite_asm();
    for(py=6;  py<182; py+=18)
    for(px=24; px<222; px+=1)
      put_sprite_asm();
#else
    for(;;) {
        x = pos_x_table[t];
        y = pos_y_table[t];
        t++;

        cur_buffer_ptr = &buffers[active_screen*(40*HEIGHT)];

        px =x+20;
        py = y;
        put_sprite_asm();

        memcpy(screen_ptr, cur_buffer_ptr, 40*HEIGHT);

        active_screen++;
        if(active_screen == BUFFER_COUNT)
            active_screen = 0;
    }
#endif
}
