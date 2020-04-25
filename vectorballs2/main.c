#include <lib.h>
#include <math.h>

#define u8  unsigned char
#define s8  signed char
#define u16 unsigned int
#define s16 signed int

#include "sprite.h"
#include "sphere.h"
extern void IrqOff(void);
extern void copy_buffer();

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


extern void put_sprite18_noalpha(void);
extern void put_sprite16_noalpha(void);
extern void put_sprite12_noalpha(void);
extern void put_sprite8_noalpha(void);
extern void put_sprite18_asm(void);
extern void put_sprite16_asm(void);
extern void put_sprite12_asm(void);
extern void put_sprite8_asm(void);
extern void clear_sprite18(void);
extern void clear_sprite16(void);
extern void clear_sprite12(void);
extern void clear_sprite8(void);
void (*draw_sprite[8])() = {put_sprite18_noalpha, put_sprite16_noalpha,
                            put_sprite12_noalpha, put_sprite8_noalpha,
                            put_sprite18_asm,     put_sprite16_asm,
                            put_sprite12_asm,     put_sprite8_asm};
void (*clear_sprite[8])() = {clear_sprite18, clear_sprite18,
                             clear_sprite18, clear_sprite8,
                             clear_sprite18, clear_sprite18,
                             clear_sprite18, clear_sprite8};

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
            buffer[(y*40)+0] = y&1?A_BGBLUE:A_BGBLACK;

    }

    screen_text[0] = A_BGBLACK;
    screen_text[40] = A_BGBLACK;
    screen_text[80] = A_BGBLACK;

}

void main()
{
    int i, frame;
    s8 offset_x = -35; // Max 43
    s8 offset_y = 0; // Max 20
    s8 inc_x = 1;
    s8 inc_y = 2;
    IrqOff();
    gen_tables();
    hires();
    memset(buffer , 64, 200*40);
    set_colors();
    memcpy(screen, buffer, 200*40);
    frame = 0;

    for(;;) {
        for(i=0; i<(PT_COUNT*3); i+=3) {
            u8 *c = &anim[frame];
            u8 s = c[i+2];
            px = c[i]+offset_x;
            py = c[i+1]+offset_y;
            draw_sprite[s]();
        }
        copy_buffer();

        for(i=0; i<(PT_COUNT*3); i+=3) {
            u8 *c = &anim[frame];
            u8 s = c[i+2];
            px = c[i]+offset_x;
            py = c[i+1]+offset_y;

            clear_sprite[s]();
        }
        frame+=(PT_COUNT*3);
        if(frame >= sizeof(anim)) {
            frame = 0;
        }

        offset_x+=inc_x;
        offset_y+=inc_y;
        if(offset_x>=43) {
            inc_x=-1;
        }
        if(offset_x<=-35) {
            inc_x=1;
        }
        if(offset_y>=10) {
            inc_y=-1;
        }
        if(offset_y<=0) {
            inc_y=1;
        }
    }
}
