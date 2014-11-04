#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>
#include "sprite.h"
#include "pc_test/cube.h"

extern void VSync(void);
extern void draw_sprite_at_address(unsigned char addrl, unsigned char addrh );
extern void clear_sprite_at_address(unsigned char x, unsigned char y);
extern void draw_sprite(unsigned char x, unsigned char y);
extern void clear_sprite(unsigned char x, unsigned char y);
extern void push_sprite_on_stack(void);
extern void IrqOff(void);
extern void draw_sprite_at_xy(unsigned char x, unsigned char y);
extern void clear_sprite_at_xy(unsigned char x, unsigned char y);
extern void clear_sprites(unsigned int offset);
extern void draw_sprites(unsigned int offset);
unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
volatile int table_y[200];


void set_colors(void) {
    int y;
    unsigned char mask = 0;
    for(y=0; y<200; y++) {
        screen[(y*40)+0] = A_FWYELLOW;
        mask++;
        if((y&mask)>64) {
            screen[(y*40)+1] = A_BGBLUE;
        } else {
            screen[(y*40)+1] = A_BGBLACK;
        }
    }

    screen_text[0] = A_BGBLACK;
    screen_text[1] = A_BGBLUE;
    screen_text[40] = A_BGBLACK;
    screen_text[41] = A_BGBLUE;
    screen_text[80] = A_BGBLACK;
    screen_text[81] = A_BGBLUE;

}

void animcube_address(void) {
    int t;
    int offset = 0;
    int frame = 0;

    push_sprite_on_stack();

    while(1) {
        offset = 0;
        frame = 0;
        while(offset<sizeof(anim)) {
            char count      = anim[offset]>>1;

            draw_sprites(offset);

            VSync();
            VSync();
            VSync();

            clear_sprites(offset);
            offset+=(count<<1)+1;

            frame++;
        }
    }
}

int main(int argc, char *argv[])
{
    IrqOff();
    hires();
    set_colors();
    animcube_address();
}


