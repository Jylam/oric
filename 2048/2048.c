#include <stdio.h>
#include <sys/graphics.h>

char *screen = (char*)0xbb80;
unsigned char board[4*4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char *values[] = {
    "    ", /* 0 */
    "2   ",
    "4   ",
    "8   ",
    "16  ",
    "32  ",
    "64  ",
    "128 ",
    "256 ",
    "512 ",
    "1024",
    "2048"
};

void init_board(void) {
    unsigned char x   = 2;
    unsigned char y   = 3;
    unsigned char x2  = 3;
    unsigned char y2  = 2;

    board[x+(y*4)] = 1;
    board[x2+(y2*4)] = 1;
}

void draw_entry(char x, char y, char value) {
    int i = 0;
    int offset = ((x*10)+2)+((y*7)+2)*40;
    char *str = values[value];

    for(i = 0; i < 4; i++) {
        screen[offset+i] = ' ';
    }
    for(i = 0; i < 4; i++) {
        screen[offset+i] = str[i];
    }
}

void draw_grid(void) {
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
            screen[x+y*40] = '|';
        }
    }

    for(y = 0; y < 29; y+=7) {
        for(x=0; x<40; x++) {
            screen[x+y*40] = '-';
        }
    }


}
void draw_board(void) {
    int x = 0;
    int y = 0;
    for(y = 0; y < 4; y++) {
        for(x = 0; x < 4; x++) {
            draw_entry(x, y, board[x+y*4]);
        }
    }
}

void clear_screen(void) {
    memset(screen, ' ', 40*28);
}

void move_up(void) {
    int x, y;

    for(x=0; x<4; x++)
    for(y=3; y>0; y--) {
        if(board[x+((y-1)*4)]==0) {
            int y2;
            for(y2=y; y2<4; y2++) {
                board[x+((y2-1)*4)] = board[x+(y2*4)];
                board[x+(y2*4)] = 0;
            }
        }
    }
}

void move_down(void) {
    int x, y;

    for(x=0; x<4; x++) {
        for(y=0; y<2; y++) {
            if(board[x+((y)*4)]==0) {
                int y2;
                for(y2=y; y2>=0; y2--) {
                    board[x+((y2+1)*4)] = board[x+((y2)*4)];
                    board[x+((y2)*4)] = 0;
                }
            }
        }
    }
}


void game(void) {
    int k = getchar();

    curmov(0, 0, MODE_SET);
    switch(k) {
        case 11:  /* Up */
            move_up();
            break;
        case 10:  /* Down */
            move_down();
            break;
        case  8:  /* Left */
            break;
        case  9:  /* Right */
            break;
    }
    draw_board();
}

int main(int argc, char *argv[]) {
    int x, y;
    clear_screen();

    curmov(0, 0, MODE_NONE);
    init_board();
    draw_grid();
    draw_board();


    while(1) {
        game();
    }

}


