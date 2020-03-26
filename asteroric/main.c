#include <lib.h>

extern void IrqOff(void);

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
volatile int table_y[200];

void set_colors(void) {
    int y;
    for(y=0; y<200; y++) {
        screen[(y*40)+0] = A_FWYELLOW;
        screen[(y*40)+1] = A_BGBLACK;
    }

    screen_text[80] = A_FWWHITE;
    screen_text[81] = A_BGBLUE;
}

void main()
{
    hires();
    set_colors();

    screen[(100*40)+2] = 0x20; // 1px
    screen[(101*40)+2] = 0x7E; // 6px

}
