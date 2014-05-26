#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>
#include "sprite.h"

#define NB_SPRITES 10
#define SPRITE_W 2
#define SPRITE_H 12

typedef struct {
    unsigned char x, y, oldx, oldy;
    char tx, ty;
} sprite;

extern void draw_sprite(unsigned char x, unsigned char y);

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
volatile unsigned int table_y[200];


sprite sprites[NB_SPRITES];

int main(int argc, char *argv[]) {
    unsigned char x=0, y=0, oldx=0, oldy=0;
    unsigned int t=0xa000;
    char tx=1, ty=1, s;

    for(y=0 ; y<200; y++) {
        table_y[y] = t;
        t+=40;
    }

#if 1
    y = 0;
    for(s=0;s<NB_SPRITES;s++) {
        sprites[s].x = sprites[s].y = sprites[s].oldx = sprites[s].oldy = 1;
        sprites[s].x = rand()&0x0F;
        sprites[s].y = rand()&0x70;
        sprites[s].tx = (rand()&0x02)-1;
        if(sprites[s].tx == 0) sprites[s].tx = 1;
        sprites[s].ty = (rand()&0x03)-1;
        if(sprites[s].ty == 0) sprites[s].ty = 1;

    }
#endif


    hires();
    setflags(getflags()&~(CURSOR|SCREEN)); // Disable cursor and scrolling

#if 0
    while(1) {
        for(y=0;y<188; y+=6) {
            for(x=0;x<40; x+=SPRITE_W) {
                draw_sprite(x, y);
                for(t=0; t < 1; t++);
            }
        }
        while(1);
    }
#else
    while(1) {
        for(s=0;s<NB_SPRITES;s++) {
            clear_sprite(sprites[s].oldx, sprites[s].oldy);
        }
        for(s=0;s<NB_SPRITES;s++) {

            sprites[s].x+=sprites[s].tx;
            sprites[s].y+=sprites[s].ty;
            if(sprites[s].x<=0)   sprites[s].tx =  -sprites[s].tx;
            if(sprites[s].x>=38)  sprites[s].tx =  -sprites[s].tx;
            if(sprites[s].y<=0)   sprites[s].ty =  -sprites[s].ty;
            if(sprites[s].y>=188) sprites[s].ty =  -sprites[s].ty;
            sprites[s].oldx = sprites[s].x;
            sprites[s].oldy = sprites[s].y;

            draw_sprite(sprites[s].x, sprites[s].y);
        }
    }
#endif
}


