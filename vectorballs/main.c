#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
extern void draw_sprite(unsigned char x, unsigned char y, unsigned char color);

int main(int argc, char *argv[]) {
    unsigned char x, y;
    int t;

    hires();
    setflags(getflags()&~(CURSOR|SCREEN)); // Disable cursor and scrolling

    while(1) {
        for(x = 0; x < 32; x++) {
            for(t=0; t < 1000; t++);
                draw_sprite(x, x, 0b01100001);

        }
    }
}


