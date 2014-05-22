#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
extern void draw_sprite(unsigned char x, unsigned char y, unsigned char color);

int main(int argc, char *argv[]) {
    int x, y;

    hires();
    setflags(getflags()&~(CURSOR|SCREEN)); // Disable cursor and scrolling

    draw_sprite(0x13, 0x37, 0x55);
}


