//#include <stdio.h>
#include <sys/graphics.h>
#include <lib.h>
#define HIRES

#ifdef HIRES
char *screen = (char*)0xa000;
#else
char *screen = (char*)0xbb80;
#endif
unsigned char board[4*4] = {0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 1,
                            0, 0, 1, 0};
char *values[] = {
    "    ", // 0
    "2   ", // 1
    "4   ", // 2
    "8   ", // 3
    "16  ", // 4
    "32  ", // 5
    "64  ", // 6
    "128 ", // 7
    "256 ", // 8
    "512 ", // 9
    "1024", // 10
    "2048"  // 11
};

int lost = 0;

void init_board(void) {
    unsigned char x   = 2;
    unsigned char y   = 3;
    unsigned char x2  = 3;
    unsigned char y2  = 2;

    board[x+(y*4)] = 1;
    board[x2+(y2*4)] = 1;
}
#ifndef HIRES
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
    int oy = 0;
    for(x=0; x<40; x++) {  // Up
        screen[x] = '-';
    }

    y = 40*40;
    for(x=0; x<40; x++) {
        screen[x+y] = '-'; // Down
    }


    for(x = 0; x < 40; x+=10) {
        oy = 0;
        for(y=0; y<40; y++) {
            screen[x+oy] = '|';
            oy+=40;
        }
    }

    oy=0;
    for(y = 0; y < 29; y+=7) {
        for(x=0; x<40; x++) {
            screen[x+oy] = '-';
        }
        oy+=280; // 40*7
    }

}
#else
#define XOFFSET 2

char c2048[] = {0b100001};

void draw_entry(char x, char y, char value) {
    int i = 0;
    int ty = 0, oy = 0;
    int offset = ((x*9)+XOFFSET)+((y*50)+15)*40;
    char *str = values[value];

    for(ty=0;ty<22; ty++) {
        for(i = 2; i < 7; i++) {
            screen[offset+oy+i] = 0b00111111;
        }
        oy+=40;
    }
}

void draw_grid(void) {
    int x = 0;
    int y = 0;
    int oy = 0;


    for(x = 2; x < 40; x+=9) {
        oy = 0;
        for(y=0; y<200; y++) {
            screen[x+y*40] = 0x60;
            oy+=40;
        }
    }

    oy=0;
    for(y = 0; y < 200; y+=50) {
        for(x=2; x<38; x++) {
            screen[x+y*40] = 0x7f;
        }
//        oy+=; // 40*7
    }
    for(x=2; x<38; x++) {
        screen[x+199*40] = 0x7f;
    }
}
#endif
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
#ifndef HIRES
    memset(screen, ' ', 40*28);
#else

#endif
}


void add_random_piece(void) {
    unsigned int count = 0;
    unsigned int id    = 0;
    unsigned int i     = 0;

    // Count empty tiles
    for(i=0; i<4*4;i++) {
        if(board[i]==0) count++;
    }

    // No free tiles, game lost
    if(count==0) {
        lost = 1;
        return;
    }

    // Chose a random free tile
    id = rand()%count;

    // Fill selected tile
    count = 0;
    for(i=0; i<4*4; i++) {
        if(board[i] == 0) {
            if(count == id) {
                board[i] = 1;
                return;
            }
            count++;
        }
    }
}

int find_next(unsigned char *b, int x, int stop) {
    int t = 0;
    if(x==0) return x;

    for(t=x-1;t>=0;t--) {
        if (b[t]!=0) {
            if (b[t]!=b[x]) {
                return t+1;
            }
            return t;
        } else {
            if (t==stop) {
                return t;
            }
        }
    }
    return x;
}

int move_line_left(unsigned char *b) {
    int x, t = 0;
    int got_move = 0;
    int stop = 0;
    int success = 0;
    for(x=0; x<4; x++) {
        if(b[x]!=0) {
            t = find_next(b, x, stop);
            if (t!=x) {
                if (b[t]!=0) {
                    stop = t+1;
                }

                if(b[t]==b[x]) {
                    b[t]=b[x]+1;
                } else {
                    b[t]=b[x];
                }
                b[x]=0;
                success = 1;
            }
        }
    }
    return success;
}

int move_left(void) {
    int y;
    int success = 0;

    for(y=0; y<4; y++) {
        unsigned char *b = &board[y*4];
        success += move_line_left(b);
    }
    return success;
}

void rotateBoardCCW(void) {
    char temp[4*4];
    memcpy(temp, board, 4*4);

    board[0+(3*4)] = temp[0+(0*4)];
    board[0+(2*4)] = temp[1+(0*4)];
    board[0+(1*4)] = temp[2+(0*4)];
    board[0+(0*4)] = temp[3+(0*4)];

    board[1+(3*4)] = temp[0+(1*4)];
    board[1+(2*4)] = temp[1+(1*4)];
    board[1+(1*4)] = temp[2+(1*4)];
    board[1+(0*4)] = temp[3+(1*4)];

    board[2+(3*4)] = temp[0+(2*4)];
    board[2+(2*4)] = temp[1+(2*4)];
    board[2+(1*4)] = temp[2+(2*4)];
    board[2+(0*4)] = temp[3+(2*4)];

    board[3+(3*4)] = temp[0+(3*4)];
    board[3+(2*4)] = temp[1+(3*4)];
    board[3+(1*4)] = temp[2+(3*4)];
    board[3+(0*4)] = temp[3+(3*4)];
}

void game(void) {
    int k = getchar();
    int got_move = 0;
    switch(k) {
        case 10:  /* Down */
            rotateBoardCCW();
            rotateBoardCCW();
            rotateBoardCCW();
            got_move = move_left();
            rotateBoardCCW();
            break;
        case 11:  /* Up */
            rotateBoardCCW();
            got_move = move_left();
            rotateBoardCCW();
            rotateBoardCCW();
            rotateBoardCCW();
            break;
        case  9:  /* Right */
            rotateBoardCCW();
            rotateBoardCCW();
            got_move = move_left();
            rotateBoardCCW();
            rotateBoardCCW();
            break;
        case  8:  /* Left */
            got_move = move_left();
            break;
    }

    if(got_move) add_random_piece();
    if(lost) {
        while(1) {
            printf("LOST\n");
        }
    }
    draw_board();
}

int main(int argc, char *argv[]) {
    int x, y;
    clear_screen();

#ifdef HIRES
    hires();
#endif
    curmov(0, 0, MODE_NONE);
    setflags(getflags()&~(CURSOR|SCREEN));
    draw_grid();
    draw_board();

    while(1) {
        game();
    }

}


