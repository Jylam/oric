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

void sleep(int v) {
    int a, b, c, d;

    a = b = c = d = v;

    while(a--) {
        b = v;
        while(b--) {
            c = v;
            while(c--) {
                d = v;
                while(d--) {

                }
            }
        }
    }
}


void animcube(void) {
    int t;
    int offset = 0;
    while(1) {
        offset = 0;
        while(offset<sizeof(anim)) {
            int i;
            char count      = anim[offset];
            int old_offset;
            offset++;
            old_offset = offset;
            for(i=0; i<count; i++) {
                draw_sprite(anim[offset], anim[offset+1]);
                offset+=3; // X,Y,Depth
            }
            for(i=0; i<5; i++) {
                sprintf(&screen_text[52], "Oui, ca clignotte.\n");
            }
            offset = old_offset;
            for(i=0; i<count; i++) {
                clear_sprite(anim[offset], anim[offset+1]);
                offset+=3; // X,Y,Depth
            }
        }
    }
}
void animcube_address(void) {
    int t;
    int offset = 0;
    int frame = 0;

    while(1) {
        offset = 0;
        frame = 0;
        while(offset<sizeof(anim)) {
            int i;
            char count      = anim[offset];
            int old_offset;
            offset++;
            old_offset = offset;
            for(i=0; i<count; i++) {
                push_sprite_on_stack();
                draw_sprite_at_address(anim[offset], anim[offset+1]);
                offset+=2; // 16bits address
            }
            //VSync();
            sprintf(&screen_text[52], "Frame %d\n", frame);

            offset = old_offset;
            for(i=0; i<count; i++) {
                clear_sprite_at_address(anim[offset], anim[offset+1]);
                offset+=2; // X,Y,Depth
            }
            frame++;
        }
    }
}

int main(int argc, char *argv[]) {
    unsigned char y;
    int t=0xa000;
    int s = 0;
    int f;
    unsigned char angle = 0;

    for(y=0 ; y<200; y++) {
        table_y[y] = t;
        t+=40;
    }

    IrqOff();
    hires();
    set_colors();
    animcube_address();
    //    vectorballs();
}


