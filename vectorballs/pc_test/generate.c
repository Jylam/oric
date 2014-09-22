#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <SDL.h>


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
    float x3, y3, z3;
    float xr, yr, zr;
    float px, py;
    float angle_x = 0.0f, angle_y = 0.0f, angle_z = 0.0f;
    int i, quit=0;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);


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

        rotateX(x, y, z, &x2, &y2, &z2,    (angle_z*M_PI/180.0f));
        rotateY(x2, y2, z2, &x3, &y3, &z3, (angle_y*M_PI/180.0f));
        rotateZ(x3, y3, z3, &xr, &yr, &zr, (angle_z*M_PI/180.0f));
        angle_z+=1.0f;

        SDL_RenderDrawPoint(renderer, xr+400, yr+300); //Renders on middle of screen.
        SDL_RenderPresent(renderer);
    }

    return 0;
}
