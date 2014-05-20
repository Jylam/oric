//#include <stdio.h>
#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>
#include "font.h"

char *screen = (char*)0xa000;
unsigned char board[4*4] = {1, 0, 11, 10,
                            2, 0, 0, 9,
                            3, 0, 0, 8,
                            4, 5, 6, 7};
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

    //board[x+(y*4)] = 1;
    //board[x2+(y2*4)] = 1;
}

void set_entry_color(unsigned char x, unsigned char y, unsigned char color) {
    unsigned int offset;
    unsigned int i = 0;
    unsigned int ty = 0;
    unsigned char tx = 0;

    unsigned char offset_x;

    offset_x = 1;
    offset = ((x)+offset_x)+((y))*40;
    for(ty=0;ty<9; ty++) {
        screen[offset+2] = color;
        screen[offset+3] = 0b01000000;
        screen[offset+4] = 0b01000000;
        screen[offset+5] = 0b01000000;
        screen[offset+6] = 0b01000000;
        screen[offset+7] = 0b01000000;
        screen[offset+8] = 0b00000111; // Ink White

        offset+=40;
    }
}

void draw_entry(unsigned char x, unsigned char y, char value) {
    unsigned int offset;
    unsigned int i = 0;
    unsigned int ty = 0, oy = 0;

    unsigned int ex;
    unsigned char w, h, offset_x;
    unsigned char *sprite = NULL;
    unsigned char color;

    switch(value) {
        case 1:
            sprite = c2;
            color  = A_FWWHITE;
            break;
        case 2:
            sprite = c4;
            color  = A_FWWHITE;
            break;
        case 3:
            sprite = c8;
            color  = A_FWWHITE;
            break;
        case 4:
            sprite = c16;
            color  = A_FWWHITE;
            break;
        case 5:
            sprite = c32;
            color  = A_FWWHITE;
            break;
        case 9:
            sprite = c512;
            color  = A_FWWHITE;
            break;
        case 10:
            sprite = c1024;
            color  = A_FWWHITE;
            break;
        case 11:
            sprite = c2048;
            color  = A_FWWHITE;
            break;
        default:
            sprite = NULL;
            color = A_FWBLACK;
            break;
    }
    set_entry_color(x, y, color);
    if(sprite == NULL)
        return;

    w        = sprite[0];
    h        = sprite[1];
    offset_x = sprite[2];
    offset = ((x)+offset_x)+((y))*40;
    oy = offset;
    ex = 3;        // Skip WxH from sprite map
    for(ty=0;ty<h; ty++) {
        for(i = 2; i < w+2; i++) {   // Skip 2 bytes of attributes at the start of the ULA line
            screen[oy+i] = sprite[ex];
            ex++;
        }
        oy+=40;
    }
}

void draw_grid(void) {
    int x = 0;
    int y = 0;
    int oy = 0;

    for(y=0;y<200;y++) {
        screen[y*40+1]   = 0x07; // Ink white
        screen[(y*40)+2] = 0x17; // Paper Black
    }

    for(x = 2; x < 40; x+=9) {
        oy = 0;
        for(y=0; y<200; y++) {
            screen[x+y*40] = 0b01100000; // Vertical Lines
            oy+=40;
        }
    }

    oy=0;
    for(y = 0; y < 240; y+=50) {
        for(x=2; x<38; x++) {
           screen[x+y*40] = 0b01111111;  // Horizontal lines
        }
    }
    for(x=2; x<38; x++) {
           screen[x+199*40] = 0b01111111; // Bottom horizontal line
    }
}
void draw_board(void) {
    unsigned int x = 0;
    unsigned int y = 0;

    for(y = 0; y < 4; y++) {
        for(x = 0; x < 4; x++) {
            draw_entry(x*9, (y*50)+20, board[x+y*4]);
        }
    }
}

void clear_screen(void) {
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

    hires();
    curmov(0, 0, MODE_NONE);
    setflags(getflags()&~(CURSOR|SCREEN));
    draw_grid();
    draw_board();

    while(1) {
        game();
    }

}


