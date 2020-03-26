#include <lib.h>

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

void main()
{
    hires();
    set_colors();
    printf("Hello World lol\n");

}
