//#include <stdio.h>
#define NULL ((void*)0)
#include <sys/graphics.h>
#include <lib.h>
#include "font.h"

int lost = 0;
unsigned char *screen = (unsigned char*)0xa000;
unsigned char board[4*4] = {0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            10, 11, 0, 0};

unsigned char* tiles[] = {
	NULL, (unsigned char*)A_BGBLACK,
	c2,   (unsigned char*)A_BGRED,
	c4,   (unsigned char*)A_BGGREEN,
	c8,   (unsigned char*)A_BGBLUE,
	c16,  (unsigned char*)A_BGMAGENTA,
	c32,  (unsigned char*)A_BGCYAN,
	c64,  (unsigned char*)A_BGRED,
	c128, (unsigned char*)A_BGGREEN,
	c256, (unsigned char*)A_BGBLUE,
	c512, (unsigned char*)A_BGMAGENTA,
	c1024,(unsigned char*)A_BGCYAN,
	c2048,(unsigned char*)A_BGRED,
};



void init_board(void) {
    add_random_piece();
    add_random_piece();
}

void set_entry_color(unsigned char x, unsigned char y, unsigned char color) {
    unsigned int offset;
    unsigned char ty;

    offset = x+1+(y+1)*40;
    for(ty=0;ty<40; ty++) {
        screen[offset+2] = color;     // Set color
        screen[offset+9] = A_BGBLACK; // Reset to black for drawing the line

	// Clear previous sprite  FIXME: don't do this if already cleared
	if(ty>18 && ty<28) {
		screen[offset+3] = 0b01000000;
		screen[offset+4] = 0b01000000;
		screen[offset+5] = 0b01000000;
		screen[offset+6] = 0b01000000;
		screen[offset+7] = 0b01000000;
	}

	offset+=40;
    }
}

void draw_entry(unsigned char x, unsigned char y, unsigned char value) {
    unsigned int ox;
    unsigned int oy;

    unsigned int ex;
    unsigned char w, h, offset_x, ty;
    unsigned char *sprite;
    unsigned char color;

    value  = value<<1;                         // Interleaved with color
    sprite = tiles[value];                     // Get tile pointer
    color  = (unsigned char)tiles[(value)+1];  // Get color, 1 byte after tile pointer

    set_entry_color(x, y, color);              // Clear tile and set color

    if(sprite == NULL)                         // Empty tile
	    return;

    w        = sprite[0]+2;  // Width, Skip 2 bytes of attributes, see ox
    h        = sprite[1];    // Height, always 9
    offset_x = sprite[2];    // Offset of the sprite, to center the tile

    ox       = 0;
    oy       = (x+offset_x); // Sprites are at Y=20, X=offset_x+x
    y       += 20;
    oy      += (y*40);       // FIXME multiplication
    ex = 3;                  // Skip WxH from sprite map

    for(ty=0;ty<h; ty++) {
    	    ox=2;           // Skip 2 bytes of attributes at the start of the ULA line
	    while(ox < w) {
		    screen[oy+ox] = sprite[ex];
		    ex++;
		    ox++;
	    }
	    oy+=40;
    }
}

// Called only one time
void draw_grid(void) {
    int x = 0;
    int y = 0;
    int oy = 0;

    // Vertical lines
    x=2;
    while(x<40) {
	    oy = 0;
	    for(y=0; y<200; y++) {
		    screen[x+y*40] = 0b01100000;
		    oy+=40;
	    }

	    x+=9;
    }
    // Horizontal lines
    oy=0;
    for(y = 0; y < 200; y+=50) {
        for(x=2; x<38; x++) {
           screen[x+y*40] = 0b01111111;  // Horizontal lines
        }
    }
    // Last line (?)
    for(x=2; x<38; x++) {
           screen[x+199*40] = 0b01111111; // Bottom horizontal line
    }
}

void draw_board(void) {
    unsigned int  x = 0;
    unsigned int  y = 0;
    unsigned int  px = 0;
    unsigned int  py = 0;
    unsigned char i  = 0;

    for(y = 0; y < 4; y++) {
    	px = 0;
        for(x = 0; x < 4; x++) {
            draw_entry(px, py, board[i++]);
	    px+=9;
        }
	py+=50;
    }
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
        init_board();
    }
    draw_board();
}

int main(int argc, char *argv[]) {
    int x, y;

    hires();
    setflags(getflags()&~(CURSOR|SCREEN)); // Disable cursor and scrolling

    init_board();
    draw_grid();
    draw_board();

    while(1) {
        game();
    }

}


