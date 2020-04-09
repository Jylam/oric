# 1 "hello_world_simple.final.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4

# 17 "/usr/include/stdc-predef.h" 3 4











































# 32 "<command-line>" 2
# 1 "hello_world_simple.final.c"
//
// This is the standard "HELLO WORLD" sample
//


# 1 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/include/lib.h" 1


void exit(int retval);


int getchar(void);
int putchar(char c);
int printf(const char *format,...);

char *itoa(int n);

int isalpha(char c);
int isupper(char c);
int islower(char c);
int isdigit(char c);
int isspace(char c);
int ispunct(char c);
int isprint(char c);
int iscntrl(char c);
int isascii(char c);
char toupper(char c);
char tolower(char c);
char toascii(char c);

char* sbrk();
char* brk();

char *strcpy(char *s1,const char * s2);
int strcmp(const char *s1,const char * s2);
int strlen(const char *s);

int memcpy(void *dst, void *src, int n);



void hires(void);
void text(void);
void ping(void);
void shoot(void);
void zap(void);
void explode(void);
void kbdclick1(void);
void kbdclick2(void);
int ink(int color);
int paper(int color);
int curset(int x,int y,int mode);
int curmov(int dx,int dy,int mode);
int draw(int dx,int dy,int mode);
int circle(int radius,int mode);
int hchar(char c,int charset,int mode);
int fill(int height,int width,char c);
int point(int x,int y);
int pattern(char style);
int play(int soundchanels,int noisechanels,int envelop,int volume);
int music(int chanel,int octave,int key,int volume);
int sound(int chanel,int period,int volume);
void w8912(unsigned char reg,unsigned char value);
char key(void);
char is_overlay_enabled();




void cls();
void lores0(void);
void lores1(void);
void gotoxy(int x, int y); 
int  get(void);			   
void cwrite(char c);			  
int  cread();				 
void cwritehdr();		     
void call(int addr);		     







void sedoric(char *command);		













int  lprintf(const char *format,...);




void file_unpack(void *ptr_dst,void *ptr_src);


































# 162 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/include/lib.h"





















//static char *textvram=(char*)48000; 








extern unsigned char OsdkTableMod6[];
extern unsigned char OsdkTableDiv6[];


//
// Some 'pseudo standard' library stuff
//
extern unsigned int randseedLow;
extern unsigned int randseedTop;
extern unsigned int pcrand();




# 6 "hello_world_simple.final.c" 2

# 1 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/include/sys/sound.h" 1









extern void ping(void);




extern void shoot(void);




extern void zap(void);




extern void explode(void);




extern void kbdclick1(void);




extern void kbdclick2(void);




   
   
   





















extern int play(int soundchanels,int noisechanels,int envelop,int volume);








# 85 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/include/sys/sound.h"

# 98 "/home/jylam/code/oric/public/pc/tools/osdk/main//Osdk/_final_/include/sys/sound.h"

extern int music(int channel,int octave,int key,int volume);





extern int sound(int channel,int period,int volume);






# 7 "hello_world_simple.final.c" 2

void main()
{
	printf("Hello World !\n");
}
