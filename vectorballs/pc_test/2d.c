#include <stdio.h>
#include <math.h>
#define FP_W 8

#define FIXED signed short

// 255 (all LSB set, all MSB clear)
#define FP_MASK ((1 << FP_W) - 1)

#define FP(a) ((a)<<FP_W)
#define INT(a) (((FIXED)a)>>FP_W)
#define FLOAT_TO_FP(a) ((a)*(float)FP_MASK)
#define FP_TO_FLOAT(a) ((a)/(float)FP_MASK)

#define FP_ADD(a, b) ((a)+(b))
#define FP_SUB(a, b) ((a)-(b))
#define FP_MUL(a, b) ((a)*INT((b)))
#define FP_DIV(a, b) ((a)/INT((b)))

#define FP_DEC(a)(((FIXED)(a & FP_MASK)<<FP_W)/(1<<FP_W))



void rotateX(FIXED x, FIXED y, FIXED angle) {
    FIXED x2;
    FIXED y2;
    FIXED s;
    // x' = x*cos(theta) - y*sin(theta)
    // y' = x*sin(theta) + y*cos(theta)
//    x2 = FP_MUL(x, FLOAT_TO_FP(cos(FP_TO_FLOAT(angle)*M_PI/180.0f))) - FP_MUL(y, FLOAT_TO_FP(sin(FP_TO_FLOAT(angle)*M_PI/180.0f)));
//    y2 = FP_MUL(x, FLOAT_TO_FP(sin(FP_TO_FLOAT(angle)*M_PI/180.0f))) + FP_MUL(y, FLOAT_TO_FP(cos(FP_TO_FLOAT(angle)*M_PI/180.0f)));


    printf("Angle %f, x %f, y %f\n", FP_TO_FLOAT(angle), FP_TO_FLOAT(x2), FP_TO_FLOAT(y2));

#if 0
    printf("Angle %f (rad %f)  %f %f   sin %f -> %04x\n",
        FP_TO_FLOAT(angle),
        FP_TO_FLOAT(angle)*M_PI/180.0f,
        FP_TO_FLOAT(x2),
        FP_TO_FLOAT(y2),
        sin(FP_TO_FLOAT(angle)*M_PI/180.0f),
        FLOAT_TO_FP(sin(FP_TO_FLOAT(angle)*M_PI/180.0f)*100.0f));
    s = FLOAT_TO_FP(sin(FP_TO_FLOAT(angle)*M_PI/180.0f));
    printf("Angle %f, Sin : %f      FP : %f\n", FP_TO_FLOAT(angle), sin(FP_TO_FLOAT(angle)*M_PI/180.0f), FP_TO_FLOAT(s));
#endif
}

void test_fp(void) {
    FIXED x = FP(10), x2;
    FIXED y = FP(0), y2;
    FIXED a = FP(0);

    while(FP_TO_FLOAT(a)<=126.f) {
        rotateX(x, y, a);
        a = FP_ADD(a, FP(10));
    }

}

void gen_tables(void) {
    float x = 10;
    float y = 0;
    float x2, y2;
    float angle = 0;
    float a;

    for(angle = 0; angle < 360.0f; angle+=10.0f) {
        a = angle*M_PI/180.0f;
        x2 = x*cos(a) - y*sin(a);
        y2 = x*sin(a) + y*cos(a);
        printf("Angle %f,   x = %f,  y = %f\n", angle, x2, y2);
    }

}

int main(int argc, char *argv[]) {

    //    test_fp();

    gen_tables();

}




