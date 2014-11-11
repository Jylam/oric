#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>

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

void clear_hires_screen(unsigned char bg) {
    int y;
    for(y=0; y<200; y++) {
        screen[y*40] = A_BGBLACK;
        screen[1+y*40] = bg;
    }
    screen_text[0] = A_BGBLACK;
    screen_text[1] = A_FWBLUE;
    screen_text[0+40] = A_BGBLACK;
    screen_text[1+40] = A_FWBLUE;
    screen_text[0+80] = A_BGBLACK;
    screen_text[1+80] = A_FWBLUE;


}


void raster(unsigned char y) {
        int offset = 1+(y*40);
        screen[offset] = A_BGBLACK;
        offset+=40;
        screen[offset] = A_BGYELLOW;
        offset+=40;
        screen[offset] = A_BGYELLOW;
        offset+=40;
        screen[offset] = A_BGMAGENTA;
        offset+=40;
        screen[offset] = A_BGRED;
        offset+=40;
        screen[offset] = A_BGMAGENTA;
        offset+=40;
        screen[offset] = A_BGYELLOW;
        offset+=40;
        screen[offset] = A_BGYELLOW;
        offset+=40;
        screen[offset] = A_BGBLACK;
        offset+=40;
}

void rasters(void) {
    int y = 0;
    int diry = 1;

    clear_hires_screen(A_BGBLACK);
    while(1) {
        raster(y);
        VSync();
        y+=diry;
        if(y==190 || y==0) {
            diry = diry==1?-1:1;
        }
    }
}


int main(int argc, char *argv[])
{
    IrqOff();
    hires();
    rasters();
}


