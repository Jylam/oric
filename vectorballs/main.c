#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
extern void draw_sprite(unsigned char x, unsigned char y, unsigned char color);

unsigned int table_y[200];


int main(int argc, char *argv[]) {
    unsigned char x=0, y=0, oldx=0, oldy=0;
    char tx=1, ty=1;
    int t=0;

    for(ty=0 ; ty<200; ty++) {
        table_y[ty] = t;
        t+=40;
    }

    hires();
    setflags(getflags()&~(CURSOR|SCREEN)); // Disable cursor and scrolling

    while(1) {
        if(x==0)  tx =  1;
        if(x==32) tx = -1;
        if(y==0)   ty =  5;
        if(y==200) ty = -5;
        x+=tx;
        y+=ty;

        for(t=0; t < 1000; t++);
        // Clear the old one
        draw_sprite(oldx, oldy, 0b01000000);
        draw_sprite(x, y, 0b01100001);
        oldx = x;
        oldy = y;
    }
}


