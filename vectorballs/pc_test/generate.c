#include <stdio.h>
#include <stdint.h>
#include <math.h>


void rotateY(float x,   float y,   float z,
             float *x2, float *y2, float *z2,
             float angle) {

    *z2 = z*cos(angle) - x*sin(angle);
    *x2 = z*sin(angle) + x*cos(angle);
    *y2 = y;
}
void rotateX(float x,   float y,   float z,
             float *x2, float *y2, float *z2,
             float angle) {

    *y2 = y*cos(angle) - z*sin(angle);
    *z2 = y*sin(angle) + z*cos(angle);
    *x2 = x;
}

void rotateZ(float x,   float y,   float z,
             float *x2, float *y2, float *z2,
             float angle) {
    *x2 = x*cos(angle) - y*sin(angle);
    *y2 = x*sin(angle) + y*cos(angle);
    *z2 = z;
}


int main(int argc, char*argv[]) {

    float x=100.0f, y=0.0f, z=0.0f;
    float x2, y2, z2;
    float angle = 0.0f;
    int i;

    for(i = 0; i <= 180; i++) {
        rotateY(x, y, z, &x2, &y2, &z2, (angle*M_PI/180.0f));
        printf("Angle %f\t: %f\t%f\t%f\n", angle, x2, y2, z2);
        angle+=1.0f;
    }

    return 0;
}
