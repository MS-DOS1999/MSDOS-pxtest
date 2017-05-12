#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>

#define VIDEO_INT 0x10
#define SET_MODE 0x00
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200


typedef unsigned char byte;
typedef unsigned short word;

byte *VGA=(byte *)0xA0000000L;

void set_mode(byte mode){
 union REGS regs;
 regs.h.ah = SET_MODE;
 regs.h.al = mode;
 int86(VIDEO_INT, &regs, &regs);
}

void draw_pixel_fast(int x, int y, byte color){
 VGA[y*SCREEN_WIDTH+x]=color;
}


void main(){

 int color, x, y;

 word i;

 set_mode(VGA_256_COLOR_MODE);

 srand(time(NULL));
 for(i=0; i<= 5000; i++){
  x = rand()%SCREEN_WIDTH;
  y = rand()%SCREEN_HEIGHT;
  color = rand()%256;
  draw_pixel_fast(x, y, color);
 }

 getchar();
 set_mode(TEXT_MODE);
 return;
}