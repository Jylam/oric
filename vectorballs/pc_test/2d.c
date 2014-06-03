#include <stdio.h>
#include <math.h>

#define FP_W 8

#define FIXED unsigned short

// 255 (all LSB set, all MSB clear)
#define FP_MASK ((1 << FP_W) - 1)

#define FP(a) ((a)<<FP_W)
#define INT(a) (((FIXED)a)>>FP_W)
#define FLOAT_TO_FP(a) ((a)*(float)FP_MASK)
#define FP_TO_FLOAT(a) (((signed short)a)/(float)FP_MASK)

#define FP_ADD(a, b) ((a)+(b))
#define FP_SUB(a, b) ((a)-(b))
#define FP_MUL(a, b) ((a)*INT((b)))
#define FP_DIV(a, b) ((a)/INT((b)))

#define FP_DEC(a)(((FIXED)(a & FP_MASK)<<FP_W)/(1<<FP_W))

#include "tables.h"


void rotateX(FIXED x, FIXED y, FIXED cosa, FIXED sina) {
        float x2, y2;

        x2 = ((x*cosa)>>FP_W)-((y*sina)>>FP_W); // Result is wrong, cosa is fixed point and it shouldn't
        y2 = ((x*sina)>>FP_W)+((y*cosa)>>FP_W);

        printf("%f  %f  ->  %f  %f\n", FP_TO_FLOAT(x), FP_TO_FLOAT(y), FP_TO_FLOAT(x2), FP_TO_FLOAT(y2));

}

void test_fp(void) {
    FIXED x = FP(10);
    FIXED y = FP(0);
    FIXED x2, y2;
    float angle;
    float a;
    int i = 0;

    for(i=0; i<256; i++) {
        rotateX(x, y, cosa88[i], sina88[i]);

       }

}

void gen_tables(void) {
    FIXED x = FP(10);
    FIXED y = FP(0);
    FIXED x2, y2;
    float angle;
    float a;
    int i = 0;

    printf("FIXED cosa88[] = {\n");
    for(i=0; i<256; i++) {
        FIXED cosa;
        angle+=(360.0f/256.0f);
        float a = (angle*M_PI/180.0f);
        cosa = FLOAT_TO_FP(cos(a));

        printf("0x%04x, ", cosa);
       }
    printf("\n};\n");

    printf("FIXED sina88[] = {\n");
    for(i=0; i<256; i++) {
        FIXED sina;
        angle+=(360.0f/256.0f);
        float a = (angle*M_PI/180.0f);
        sina = FLOAT_TO_FP(sin(a));

        printf("0x%04x, ", sina);
       }
    printf("\n};\n");
}

int main(int argc, char *argv[]) {

    test_fp();

//    gen_tables();

}




