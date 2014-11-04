#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <SDL.h>

#define FOV 200
//#define WIDTH 800
//#define HEIGHT 600
#define WIDTH 36
#define HEIGHT 200

void rotateY(double x,   double y,   double z,
        double *x2, double *y2, double *z2,
        double angle) {

    *z2 = z*cos(angle) - x*sin(angle);
    *x2 = z*sin(angle) + x*cos(angle);
    *y2 = y;
}
void rotateX(double x,   double y,   double z,
        double *x2, double *y2, double *z2,
        double angle) {

    *y2 = y*cos(angle) - z*sin(angle);
    *z2 = y*sin(angle) + z*cos(angle);
    *x2 = x;
}

void rotateZ(double x,   double y,   double z,
        double *x2, double *y2, double *z2,
        double angle) {
    *x2 = x*cos(angle) - y*sin(angle);
    *y2 = x*sin(angle) + y*cos(angle);
    *z2 = z;
}


#if 0
#define D 10.0f
double vertices[] = {-D,   D, -D,
                 D,   D, -D,
                 D,  -D, -D,
                -D,  -D, -D,
                -D,   D, D,
                 D,   D, D,
                 D,  -D, D,
                -D,  -D, D,
};

int cube_size = sizeof(vertices)/sizeof(double);
#else
double *vertices;
int vert_size = 0;
#endif
void generate_sphere(double radius, unsigned int rings, unsigned int sectors)  {
    double *v;
    double const R = 1./(double)(rings-1);
    double const S = 1./(double)(sectors-1);
    double r, s;
//    printf("malloc %d\n", (size));
//    vertices = malloc(((int)rings) * (int)(sectors) * 3);
    vertices = malloc(1000000);
    v=vertices;
    vert_size=0;

    for(r = 1; r < rings-1; r++) {
        //printf("Ring %d\n", r);
        for(s = 0; s < sectors; s++) {
      //      printf("Sector %d\n", s);
            double y = sin( -M_PI_2 + M_PI * (double)r * (double)R );
            double x = cos(2.0*M_PI * (double)s * (double)S) * sin( M_PI * (double)r * (double)R );
            double z = sin(2.0*M_PI * (double)s * (double)S) * sin( M_PI * (double)r * (double)R );
    //        printf("--------> %f %f %f\n", x, y, z);
            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;
            vert_size+=3;
        }
    }
}

int main(int argc, char*argv[]) {

    double x=100.0f, y=0.0f, z=100.0f;
    double x2, y2, z2;
    double x3, y3, z3;
    double xr, yr, zr;
    double px, py;
    double angle_x = 0.0f, angle_y = 0.0f, angle_z = 0.0f;
    double cam_x = 0.0f, cam_y = 0.0f, cam_z = -150.0f;
    int quit=0, curframe = 0, outsize=0;
    char *outbuf = NULL;
    unsigned int size = 0;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    //generate_sphere(15, 10, 15);
    generate_sphere(15, 5, 5);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    printf("unsigned char anim[] = {\n");

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
        for(p = 0; p < vert_size; p+=3) {
            x = vertices[p];
            y = vertices[p+1];
            z = vertices[p+2];

            rotateX(x,  y,  z,  &x2, &y2, &z2, (angle_x*M_PI/180.0f));
            rotateY(x2, y2, z2, &x3, &y3, &z3, (angle_y*M_PI/180.0f));
            rotateZ(x3, y3, z3, &xr, &yr, &zr, (angle_z*M_PI/180.0f));

            xr-=cam_x;
            yr-=cam_y;
            zr-=cam_z;

            yr*=4.0f;
            xr/=1.f;
            if(zr+cam_z<=100.0f) {
                px = xr * FOV / zr;
                py = yr * FOV / zr;
                px+=(double)WIDTH/2.0f;
                py+=(double)HEIGHT/2.0f;
                if(px>=2.0f && px<=WIDTH && py>=0.0f && py<=HEIGHT) {
                    unsigned int address = 0xa000 + (((unsigned int)px)+(((unsigned int)py)*40));
                    SDL_RenderDrawPoint(renderer, px, py); //Renders on middle of screen.
            //        printf( "\t%f\t%f\t%f\n", px, py, zr);
                    //    sprintf(tmpstr, "%u,%u,%u, ", (unsigned int)px, (unsigned int)py, (unsigned int)zr);
                    //sprintf(tmpstr, "0x%02X,0x%02X, /* %d %d */", address&0xFF, address>>8, ((unsigned int)px),((unsigned int)py));
                    sprintf(tmpstr, "0x%02X,0x%02X,\n", ((unsigned int)px),((unsigned int)py));
                    size+=2;
                    outsize+=strlen(tmpstr)+1;
                    outbuf = realloc(outbuf, outsize);
                    strncat(outbuf, tmpstr, 1000);
                    visible++;
                }
            } else {
            }
        }
        size++;
        printf("%u,%s // Offset %d\n", visible*2, outbuf, size);
        free(outbuf);
        outbuf = NULL;
        visible = 0;
        angle_x+= 1.0;
        angle_y+= 3;
        angle_z+= sin(curframe*M_PI/180.0);

        if(curframe>=600) {
            quit = 1;
        }
        //if(angle_z >= 360.0f) {
        //    angle_x = angle_y = angle_z = 0.0f;
        //    quit = 1;
        //}
        if(angle_x>=360.0f) angle_x = 0.0f;
        if(angle_y>=360.0f) angle_y = 0.0f;
        if(angle_z>=360.0f) angle_z = 0.0f;

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
//            SDL_Delay(50);
        curframe++;
    }
    printf("};// Size %d\n", size);
    return 0;
}
