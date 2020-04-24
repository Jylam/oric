#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

#include "sprite.h"
//#include "cube.h"
#include "sphere.h"
extern void IrqOff(void);
extern void put_sprite18_noalpha(); // Uses _px and _py
extern void copy_buffer();
extern void clear_buffer();

u8 *screen = (u8*)0xa000;
u8 *screen_text = (u8*)0xbf68;

u8 table_yLOW[200];
u8 table_yHIGH[200];
u8 table_mul6[240];
u8 sprite_ptrs18LOW[6];
u8 sprite_ptrs18HIGH[6];
u8 sprite_alpha_ptrs18LOW[6];
u8 sprite_alpha_ptrs18HIGH[6];
u8 sprite_ptrs16LOW[6];
u8 sprite_ptrs16HIGH[6];
u8 sprite_alpha_ptrs16LOW[6];
u8 sprite_alpha_ptrs16HIGH[6];
u8 sprite_ptrs12LOW[6];
u8 sprite_ptrs12HIGH[6];
u8 sprite_alpha_ptrs12LOW[6];
u8 sprite_alpha_ptrs12HIGH[6];
u8 sprite_ptrs8LOW[6];
u8 sprite_ptrs8HIGH[6];
u8 sprite_alpha_ptrs8LOW[6];
u8 sprite_alpha_ptrs8HIGH[6];
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

        sprite_ptrs18LOW[y] = ((u16) sprite18_data +y*4*18)&0x00FF;
        sprite_ptrs18HIGH[y] = ((u16) (sprite18_data +y*4*18)&0xFF00)>>8;
        sprite_alpha_ptrs18LOW[y] = ((u16) sprite18_alpha_data +y*4*18)&0x00FF;
        sprite_alpha_ptrs18HIGH[y] = ((u16) (sprite18_alpha_data +y*4*18)&0xFF00)>>8;

        sprite_ptrs16LOW[y] = ((u16) sprite16_data +y*4*16)&0x00FF;
        sprite_ptrs16HIGH[y] = ((u16) (sprite16_data +y*4*16)&0xFF00)>>8;
        sprite_alpha_ptrs16LOW[y] = ((u16) sprite16_alpha_data +y*4*16)&0x00FF;
        sprite_alpha_ptrs16HIGH[y] = ((u16) (sprite16_alpha_data +y*4*16)&0xFF00)>>8;

        sprite_ptrs12LOW[y] = ((u16) sprite12_data +y*4*14)&0x00FF;
        sprite_ptrs12HIGH[y] = ((u16) (sprite12_data +y*4*14)&0xFF00)>>8;
        sprite_alpha_ptrs12LOW[y] = ((u16) sprite12_alpha_data +y*4*14)&0x00FF;
        sprite_alpha_ptrs12HIGH[y] = ((u16) (sprite12_alpha_data +y*4*14)&0xFF00)>>8;

        sprite_ptrs8LOW[y] = ((u16) sprite8_data +y*4*12)&0x00FF;
        sprite_ptrs8HIGH[y] = ((u16) (sprite8_data +y*4*12)&0xFF00)>>8;
        sprite_alpha_ptrs8LOW[y] = ((u16) sprite8_alpha_data +y*4*12)&0x00FF;
        sprite_alpha_ptrs8HIGH[y] = ((u16) (sprite8_alpha_data +y*4*12)&0xFF00)>>8;
    }
}

void set_colors(void) {
    int y;
    unsigned char mask = 0;

    for(y=0; y<200; y++) {
            buffer[(y*40)+1] = (y&1)?A_FWYELLOW:A_FWGREEN;
            buffer[(y*40)+0] = A_BGBLUE;
    }

    screen_text[0] = A_BGBLUE;
    screen_text[40] = A_BGBLUE;
    screen_text[80] = A_BGBLUE;

}

void main()
{
    int i, frame;
    IrqOff();
    gen_tables();
    hires();
    memset(buffer , 64, 200*40);
    set_colors();
    memcpy(screen, buffer, 200*40);
    frame = 0;
    py = 0;
    px = 20;
    for(;;) {
        for(i=0; i<(PT_COUNT*3); i+=3) {
            u8 *c = &anim[frame];
            px = c[i];
            py = c[i+1];
            if(c[i+2] == 0) {
                put_sprite18_noalpha();
            } else if(c[i+2] == 1) {
                put_sprite16_noalpha();
            } else if(c[i+2] == 2) {
                put_sprite12_noalpha();
            } else if(c[i+2] == 3) {
                put_sprite8_noalpha();
            } else if(c[i+2] == 4) {
                put_sprite18_asm();
            } else if(c[i+2] == 5) {
                put_sprite16_asm();
            } else if(c[i+2] == 6) {
                put_sprite12_asm();
            } else if(c[i+2] == 7) {
                put_sprite8_asm();
            }
        }
        copy_buffer();
        //clear_buffer();
        for(i=0; i<(PT_COUNT*3); i+=3) {
            u8 *c = &anim[frame];
            px = c[i];
            py = c[i+1];

            clear_sprite();
        }
        frame+=(PT_COUNT*3);
        if(frame >= sizeof(anim)) {
            frame = 0;
        }
    }
}
