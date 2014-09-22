#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <SDL.h>

#define FOV 200
#define WIDTH 40
#define HEIGHT 200

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


#define D 10.0f
float cube[] = {-D,   D, -D,
                 D,   D, -D,
                 D,  -D, -D,
                -D,  -D, -D,
                -D,   D, D,
                 D,   D, D,
                 D,  -D, D,
                -D,  -D, D,
};

int main(int argc, char*argv[]) {

    float x=100.0f, y=0.0f, z=100.0f;
    float x2, y2, z2;
    float x3, y3, z3;
    float xr, yr, zr;
    float px, py;
    float angle_x = 0.0f, angle_y = 0.0f, angle_z = 0.0f;
    float cam_x = 0.0f, cam_y = 0.0f, cam_z = -150.0f;
    int quit=0, curframe = 0, outsize=0;
    char *outbuf = NULL;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

   printf("unsigned char anim[] {\n");

    while(!quit) {
        while (SDL_PollEvent(&e)){
            //If user closes the window
            if (e.type == SDL_QUIT){
                quit = 1;
            }
            //If user presses any key
            if (e.type == SDL_KEYDOWN){
                quit = 1;
            }
            //If user clicks the mouse
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = 1;
            }
        }

//        printf("Frame %d\n", curframe);
        int p;
        char tmpstr[1000];
        int visible = 0;
        outbuf = calloc(1,1);
        for(p = 0; p < sizeof(cube)/sizeof(float); p+=3) {
            x = cube[p];
            y = cube[p+1];
            z = cube[p+2];

            rotateX(x,  y,  z,  &x2, &y2, &z2, (angle_x*M_PI/180.0f));
            rotateY(x2, y2, z2, &x3, &y3, &z3, (angle_y*M_PI/180.0f));
            rotateZ(x3, y3, z3, &xr, &yr, &zr, (angle_z*M_PI/180.0f));

            xr-=cam_x;
            yr-=cam_y;
            zr-=cam_z;

            yr*=3.0f;


            if(zr>=0.0f) {
                px = xr * FOV / zr;
                py = yr * FOV / zr;
                px+=WIDTH/2;
                py+=HEIGHT/2;
                if(px>=0.0f && px<=WIDTH && py>=0.0f && py<=HEIGHT) {

                    SDL_RenderDrawPoint(renderer, px, py); //Renders on middle of screen.
                    //sprintf(tmpstr, "\t%f\t%f\t%f\n", px, py, zr);
                    sprintf(tmpstr, "0x%02X,0x%02X,0x%02X, ", (unsigned int)px, (unsigned int)py, (unsigned int)zr);
                    outsize+=strlen(tmpstr)+1;
                    outbuf = realloc(outbuf, outsize);
                    strncat(outbuf, tmpstr, 1000);
                    visible++;
                }
            } else {
                tmpstr[0] = 0;
            }
        }
        printf("%u,%s\n", visible, outbuf);
        free(outbuf);
        outbuf = NULL;
        visible = 0;
        angle_x+=1.0f;
        angle_y+=.5f;
        angle_z+=.5f;

        if(angle_x >= 360.0f) {
            angle_x = angle_y = angle_z = 0.0f;
            quit = 1;
        }
        if(angle_x>=360.0f) angle_x = 0.0f;
        if(angle_y>=360.0f) angle_y = 0.0f;
        if(angle_z>=360.0f) angle_z = 0.0f;

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(5);
        curframe++;
    }
    printf("};\n");
    return 0;
}
