#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>
#include "tables.h"
#include "sprite.h"

#define NB_SPRITES 10
#define SPRITE_W 2
#define SPRITE_H 12

typedef struct {
    float x, y, z;
} vec3;

typedef struct {
    vec3 pos;
    unsigned char x, y, oldx, oldy;
    char tx, ty;
} sprite;

extern void draw_sprite(unsigned char x, unsigned char y);

unsigned char *screen = (unsigned char*)0xa000;
unsigned char *screen_text = (unsigned char*)0xbf68;
volatile unsigned int table_y[200];


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

#define FP_DEC(a)(((unsigned int)(a & FP_MASK)<<FP_W)/(1<<FP_W))

void test_fp(void) {
    unsigned int x = FP(100);
    unsigned int y = FP(30);
    unsigned int price = FP(1);

    for(x=0; x<10; x++) {
        price = sin[x];
        printf("%d\n", INT(price));
    }

    while(1);

}


void set_colors(void) {
    unsigned int y;
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
    unsigned int t=0xa000;
    char tx=1, ty=1;
    int s = 0;
    unsigned int f;

    test_fp();
    for(s=0; s<NB_SPRITES; s++) {
        f = 200.0f-s;
        sprites[s].pos.x =  f;
        printf("%d",        s);
        printf(" %f   ",    sprites[s].pos.x);
        printf("f is %f\n", f);
        sprites[s].pos.y = 0.0f;
        sprites[s].pos.z = 0.0f;
    }
while(1);
    for(y=0 ; y<200; y++) {
        table_y[y] = t;
        t+=40;
    }

#if 1
    y = 0;
    for(s=0;s<NB_SPRITES;s++) {
        sprites[s].x = sprites[s].y = sprites[s].oldx = sprites[s].oldy = 2;
        sprites[s].x = (rand()&0x0F)+2;
        sprites[s].y = rand()&0x70;
        sprites[s].tx = (rand()&0x02)-1;
        if(sprites[s].tx == 0) sprites[s].tx = 4;
        sprites[s].ty = (rand()&0x03)-1;
        if(sprites[s].ty == 0) sprites[s].ty = 4;

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
    set_colors();
    while(1) {
        for(s=0;s<NB_SPRITES;s++) {
            clear_sprite(sprites[s].oldx, sprites[s].oldy);
        }
        for(s=0;s<NB_SPRITES;s++) {

            sprites[s].x+=sprites[s].tx;
            sprites[s].y+=sprites[s].ty;
            if(sprites[s].x<=2)   sprites[s].tx =  -sprites[s].tx;
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


