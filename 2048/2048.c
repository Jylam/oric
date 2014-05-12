#include <stdio.h>
#include <sys/graphics.h>

char *screen = (char*)0xbb80;
char board[4*4] = {0, 1, 2, 3};


void draw_board(void) {
    int x = 0;
    int y = 0;

    for(x=0; x<40; x++) {
        screen[x+y*40] = '-';
    }

    y = 40;
    for(x=0; x<40; x++) {
        screen[x+y*40] = '-';
    }

    for(x = 0; x < 40; x+=10) {
        for(y=0; y<40; y++) {
            screen[x+y*40] = 'l';
        }
    }

    for(y = 0; y < 29; y+=7) {
        for(x=0; x<40; x++) {
            screen[x+y*40] = '-';
        }
    }


    for(y = 0; y < 4; y++) {
        for(x = 0; x < 4; x++) {
            int i = 0;
            char str[5];
            curset((x*10)+2, (y*7)+2, MODE_NONE);
            sprintf(str, "%d", board[x+y*4]);
        }
    }


}

void clear_screen(void) {
    memset(screen, ' ', 40*28);
}


void game(void) {
    /*draw_board();*/
}

int main(int argc, char *argv[]) {
    curset(0, 0, MODE_NONE);
    clear_screen();
    draw_board();

    while(1) {
        game();
    }

}


