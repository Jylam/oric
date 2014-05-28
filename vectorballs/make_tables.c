#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int i, n=0;

    printf("unsigned int sin[] = {\n");

    for(i=0;i<255;i++) {

        printf("0x%04x, ", ((int)(sin((float)i*180.0f/M_PI)*256.0f))&0xFFFF);

        if((n++) == 16) {
            printf("\n");
            n=0;
        }
    }
    printf("};\n");

}
