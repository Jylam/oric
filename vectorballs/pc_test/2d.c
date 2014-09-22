#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FP_W 8

#define FIXED int16_t

// 255 (all LSB set, all MSB clear)
#define FP_MASK ((1 << FP_W) - 1)

#define FP(a) (((a)<<FP_W)&0xFFFF)
#define INT(a) ((a)>>FP_W)
#define FLOAT_TO_FP(a) ((a)*(float)FP_MASK)
#define FP_TO_FLOAT(a) (((FIXED)(a&0xFFFF))/(float)FP_MASK)

#define FP_ADD(a, b) ((a)+(b))
#define FP_SUB(a, b) ((a)-(b))
#define FP_MUL(a, b) ((a)*INT((b)))
#define FP_DIV(a, b) ((a)/INT((b)))

#define FP_DEC(a)(((FIXED)(a & FP_MASK)<<FP_W)/(1<<FP_W))

//#include "tables.h"


void rotateX(FIXED x, FIXED y, FIXED cosa, FIXED sina) {
    FIXED x2, y2;


    printf("cos %04X  sin %04X  (%f %f)\n", (FIXED)cosa, (FIXED)sina, FP_TO_FLOAT(cosa), FP_TO_FLOAT(sina));
    x2 = ((x*cosa)>>FP_W)-((y*sina)>>FP_W);
    y2 = ((x*sina)>>FP_W)+((y*cosa)>>FP_W);

//    printf("%d  %d\n", INT(x2), INT(y2));
}

void test_fp(void) {
    FIXED x = FP(10);
    FIXED y = FP(0);
    FIXED x2, y2;
    int i = 0;


    for(i=0; i<256; i++) {
        //rotateX(x, y, cosa88[i], sina88[i]);
    }

}

// TODO  generate 1/sin(a) and 1/cos(a) to get big numbers and get that in the MSB
// The multiplication will become a division, but it will eliminate the shifts
void gen_tables(void) {
    FIXED x = FP(10);
    FIXED y = FP(0);
    FIXED x2, y2;
    float angle;
    float a;
    int i = 0;

    printf("FIXED cosa88[] = {\n");
    for(i=0; i<256; i++) {
        float a = (angle*M_PI/180.0f);
        FIXED cosa = FLOAT_TO_FP((1.0f/cos(a)));

//        printf("%d, angle %f, %04x, %f, ____  %f\n", i, angle, cosa, FP_TO_FLOAT(cosa), 1.0f/cos(a));
        if(cosa != 0x0000)
        printf("0x%04x, /* %d */\n", cosa&0xFFFF, FP_TO_FLOAT(cosa), cosa);
        else
        printf("0x2896, /* %d */\n", cosa);

        angle+=(360.0f/256.0f);
    }
    printf("\n};\n");

    printf("FIXED sina88[] = {\n");
    for(i=0; i<256; i++) {
        float a = (angle*M_PI/180.0f);
        FIXED sina = FLOAT_TO_FP(1.0f/sin(a));

        if(sina != 0x0000)
        printf("0x%04x, \n", sina&0xFFFF);
        else
        printf("0x2896, \n");
        angle+=(360.0f/256.0f);
    }
    printf("\n};\n");
}

int main(int argc, char *argv[]) {

//    test_fp();

    gen_tables();

}




