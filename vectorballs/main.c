#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
extern void draw_sprite(unsigned char x, unsigned char y, unsigned char color);

unsigned int table_y[200];

typedef struct {
    unsigned char x, y, oldx, oldy;
    char tx, ty;
} sprite;

#define NB_SPRITES 5
sprite sprites[NB_SPRITES];

int main(int argc, char *argv[]) {
    unsigned char x=0, y=0, oldx=0, oldy=0;
    unsigned int t=0xa000;
    char tx=1, ty=1, s;

    for(y=0 ; y<200; y++) {
        table_y[y] = t;
        t+=40;
    }
    y = 0;

    for(s=0;s<NB_SPRITES;s++) {
        sprites[s].x = sprites[s].y = sprites[s].oldx = sprites[s].oldy = 1;
        sprites[s].x = rand()&0x0F;
        sprites[s].y = rand()&0x7F;
        sprites[s].tx = (rand()&0x01)+1;
        sprites[s].ty = (rand()&0x07)+1;
    }

    hires();
    setflags(getflags()&~(CURSOR|SCREEN)); // Disable cursor and scrolling

    while(1) {
        for(s=0;s<NB_SPRITES;s++) {

            if(sprites[s].x<=0)   sprites[s].tx =   -sprites[s].tx;
            if(sprites[s].x>=32)  sprites[s].tx =   -sprites[s].ty;
            if(sprites[s].y<=0)   sprites[s].ty =  -sprites[s].ty;
            if(sprites[s].y>=199) sprites[s].ty =  -sprites[s].ty;
            sprites[s].x+=sprites[s].tx;
            sprites[s].y+=sprites[s].ty;

            // Clear the old one
            draw_sprite(sprites[s].oldx, sprites[s].oldy, 0b01000000);
            draw_sprite(sprites[s].x, sprites[s].y, 0b01001100);
            sprites[s].oldx = sprites[s].x;
            sprites[s].oldy = sprites[s].y;
        }
        for(t=0; t < 1000; t++);
    }
}


