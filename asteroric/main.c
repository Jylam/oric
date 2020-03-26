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

int abs(int v) {
    if(v<0) return -v;
    return v;
}

void line(int x0, int y0, int x1, int y1) {

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){
//        setPixel(x0,y0);
        screen[(y0*40)+x0] = 0x20;
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}


void main()
{
    hires();
    set_colors();

    //screen[(100*40)+2] = 0x20; // 1px
    //screen[(101*40)+2] = 0x7E; // 6px

    line(10, 10, 35, 100);


}
