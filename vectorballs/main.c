#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>
#include "tables.h"
#include "sprite.h"

#define NB_SPRITES 9
#define SPRITE_W 2
#define SPRITE_H 12

#define FIXED int

typedef struct {
    FIXED ox, oy, oz;
    FIXED x, y, z;
    FIXED oldx, oldy, oldz;
} sprite;

extern void VSync(void);
extern void draw_sprite(unsigned char x, unsigned char y);
extern void clear_sprite(unsigned char x, unsigned char y);
extern void IrqOff(void);

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
volatile FIXED table_y[200];


sprite sprites[NB_SPRITES];

// 2^8 = 256
#define FP_W 8
// 255 (all LSB set, all MSB clear)
#define FP_MASK ((1 << FP_W) - 1)

#define FP(a) ((a)<<FP_W)
#define INT(a) ((a)>>FP_W)

#define FP_ADD(a, b) ((a)+(b))
#define FP_SUB(a, b) ((a)-(b))
#define FP_MUL(a, b) ((a)*INT((b)))
#define FP_DIV(a, b) ((a)/INT((b)))

#define FP_DEC(a)(((FIXED)(a & FP_MASK)<<FP_W)/(1<<FP_W))

#include "pc_test/tables.h"


//x' = x*cos q - y*sin q
//y' = x*sin q + y*cos q
//z' = z
void rotateZ(FIXED x, FIXED y, FIXED cosa, FIXED sina, FIXED *x2, FIXED *y2) {
    *x2 = ((x/cosa))-((y/sina));
    *y2 = ((x/sina))+((y/cosa));
}
//y' = y*cos q - z*sin q
//z' = y*sin q + z*cos q
//x' = x
void rotateX(FIXED y, FIXED z, FIXED cosa, FIXED sina, FIXED *y2, FIXED *z2) {
    *y2 = ((y/cosa))-((z/sina));
    *z2 = ((y/sina))+((z/cosa));
}
// z' = z*cos q - x*sin q
// x' = z*sin q + x*cos q
// y' = y
void rotateY(FIXED x, FIXED z, FIXED cosa, FIXED sina, FIXED *x2, FIXED *z2) {
    *x2 = ((z/cosa))-((x/sina));
    *z2 = ((z/sina))+((x/cosa));
}


void vectorballs(void) {
    unsigned char angle = 0;
    static FIXED x2, y2, z2;
    unsigned char s = 0;

    for(s=0;s<NB_SPRITES/2;s++) {
        sprites[s].ox = FP(s*16)-FP(((NB_SPRITES/2)*16));
        sprites[s].oy = FP(0);
        sprites[s].oz = 0;
    }
    for(s=NB_SPRITES/2;s<NB_SPRITES;s++) {
        sprites[s].ox = FP(0);
        sprites[s].oy = FP(s*16)-FP(((NB_SPRITES)*16));
        sprites[s].oz = 0;
    }


    s = 0;

    while(1) {
        for(s=0; s<NB_SPRITES; s++) {

            x2 = sprites[s].ox;
            y2 = sprites[s].oy;
            z2 = sprites[s].oz;
            rotateZ(sprites[s].ox, sprites[s].oy, cosa88[angle], sina88[angle], &x2, &y2);
//            rotateY(sprites[s].ox, sprites[s].oz, cosa88[angle], sina88[angle], &x2, &z2);
            x2 = FP(x2);
            y2 = FP(y2);
            z2 += 255;
            z2 = z2; // Zoom

            if(z2>0) {
                x2 = x2/(z2);
                y2 = y2/(z2);
                sprites[s].x = ((x2)/6)+20;
                sprites[s].y = (y2)+100;
            } else {
                sprites[s].x = 2;
                sprites[s].y = 0;
            }
        }

        for(s=0; s<NB_SPRITES; s++) {
            if((sprites[s].oldx>2) && (sprites[s].oldy>0) && (sprites[s].oldx<36) && (sprites[s].oldy<200))
            clear_sprite(sprites[s].oldx, sprites[s].oldy);
        }
        for(s=0; s<NB_SPRITES; s++) {
            if((sprites[s].x>2) && (sprites[s].y>0) && (sprites[s].x<36) && (sprites[s].y<200)) {
            draw_sprite(sprites[s].x, sprites[s].y);
            }
            sprites[s].oldx = sprites[s].x;
            sprites[s].oldy = sprites[s].y;
        }
        VSync();
        angle+=1;
    }


}


void set_colors(void) {
    FIXED y;
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

int main(int argc, char *argv[]) {
    unsigned char y;
    FIXED t=0xa000;
    int s = 0;
    FIXED f;
    unsigned char angle = 0;
    static FIXED x2, y2;

    for(y=0 ; y<200; y++) {
        table_y[y] = t;
        t+=40;
    }

    IrqOff();
    hires();
    set_colors();

    vectorballs();
}


