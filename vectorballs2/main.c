#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

#include "sprite.h"

extern void IrqOff(void);
extern void put_sprite_asm(); // Uses _px and _py
extern void copy_buffer();

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

extern u8 px, py;
extern u8 *screen_cpy_ptr;

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
    memset(buffer , 64, 200*40);

    for(y=0; y<200; y++) {
            buffer[(y*40)+1] = (y&1)?A_FWYELLOW:A_FWRED;
            buffer[(y*40)+0] = A_BGBLUE;
    }

    screen_text[0] = A_BGBLUE;
    screen_text[40] = A_BGBLUE;
    screen_text[80] = A_BGBLUE;

}

void main()
{
    u8 x, y, i;

    IrqOff();
    gen_tables();
    hires();
    set_colors();


    for(;;) {

        for(px = 20; px < 200; px+=18) {
            put_sprite_asm();
        }
        memcpy(screen, buffer, 40*100);
        //memset(buffer , 64, 200*40);
        set_colors();
        py++;
        if(py>=180) py=0;
    }
}
