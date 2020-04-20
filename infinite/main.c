#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

#include "sprite.h"
#include "sintable.h"

extern void IrqOff(void);
extern void put_sprite_asm(); // Uses _px and _py
extern void copy_buffer();
extern u16  pdbg;

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

u8 table_yLOW[200];
u8 table_yHIGH[200];
u8 table_mul6[240];
u8 sprite_ptrsLOW[6];
u8 sprite_ptrsHIGH[6];
u8 sprite_alpha_ptrsLOW[6];
u8 sprite_alpha_ptrsHIGH[6];
u8 table_pixel_value[6];
u8 table_div6[240];

extern u8 *cur_buffer_ptr;
extern u8 *screen_cpy_ptr;
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
}

void set_colors(void) {
    int y;
    unsigned char mask = 0;
    memset(screen , 64, 200*40);
    memset(buffers, 64, BUFFER_COUNT*HEIGHT*40);
    for(y=0; y<200; y++) {
        screen[(y*40)+1] = (y&1)?A_FWYELLOW:A_FWGREEN;
        mask++;
        if((y&mask)>64) {
            screen[(y*40)+0] = A_BGBLUE;
        } else {
            screen[(y*40)+0] = A_BGBLACK;
        }
    }



    for(y=0; y<BUFFER_COUNT; y++) {
            memcpy(&buffers[40*y*HEIGHT], &screen[(((200-HEIGHT)/2)*40)], 40*HEIGHT);
    }
    screen_text[0] = A_BGBLUE;
    screen_text[40] = A_BGBLUE;
    screen_text[80] = A_BGBLUE;

}
void set_colorsORIC(void) {
    int y;
    memset(buffers, 64, BUFFER_COUNT*HEIGHT*40);
    for(y=0; y<100; y++) {
        screen[(((y*2)+0)*40)+0] = A_FWYELLOW;
        screen[(((y*2)+0)*40)+1] = A_BGBLACK;
        screen[(((y*2)+1)*40)+0] = A_FWGREEN;
        screen[(((y*2)+1)*40)+1] = A_BGBLACK;
    }
    for(y=0; y<(BUFFER_COUNT*HEIGHT)/2; y++) {
        buffers[(((y*2)+0)*40)+0] = A_FWYELLOW;
        buffers[(((y*2)+0)*40)+1] = A_BGBLACK;
        buffers[(((y*2)+1)*40)+0] = A_FWGREEN;
        buffers[(((y*2)+1)*40)+1] = A_BGBLACK;
    }


    screen_text[0] = A_FWBLACK;
    screen_text[1] = A_BGBLACK;
    screen_text[40] = A_FWBLACK;
    screen_text[41] = A_BGBLACK;
    screen_text[80] = A_FWBLACK;
    screen_text[81] = A_BGBLACK;
}

void main()
{
    u8 test = 0b10000001;
    u16 anim_offset = 0;
    u8 x, y, i;
    u8 active_screen = 0;
    u16 tx = 0, ty = 0;
    u8 *screen_ptr;
    u16 y_offset = 0;

    IrqOff();
    gen_tables();
    hires();
    set_colors();


    y_offset = (table_yHIGH[((200-HEIGHT)/2)]<<8)|(table_yLOW[((200-HEIGHT)/2)]);
    screen_ptr = screen + y_offset;
    screen_cpy_ptr = screen + y_offset;

    cur_buffer_ptr = screen;
    x = 52;
    y = 30;

    for(;;) {
        x = sintable_x[tx>>8];
        y = sintable_y[ty>>8];

        tx+=355;
        ty+=812;
        cur_buffer_ptr = &buffers[active_screen*(40*HEIGHT)];

        px =x+20;
        py = y;
        put_sprite_asm();

        screen_cpy_ptr = screen_ptr;
        memcpy(screen_cpy_ptr, cur_buffer_ptr, 40*HEIGHT);

        screen_cpy_ptr+=(40*130);
        cur_buffer_ptr = &buffers[active_screen*(40*HEIGHT)];
        for(i=0; i<HEIGHT; i+=10) {
                copy_buffer(); // Copies 40 bytes from cur_buffer_ptr to screen_cpy_ptr
                cur_buffer_ptr+=400;
                screen_cpy_ptr+=80;
        }

        active_screen++;
        if(active_screen == BUFFER_COUNT)
                active_screen = 0;
    }
}
