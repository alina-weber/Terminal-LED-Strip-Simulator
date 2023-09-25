#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
//#define BG(r, g, b)  \x1b[48;0;r;g;bm
//#define FG(r, g, b)  \x1b[38;0;r;g;bm


void BG(uint8_t r, uint8_t g, uint8_t b){
  printf("\x1b[48;2;%d;%d;%dm",r,g,b);
}
void FG(uint8_t r, uint8_t g, uint8_t b){
  printf("\x1b[38;2;%d;%d;%dm",r,g,b);
}

void delay(uint32_t milliseconds){
  struct timespec waiter ={};
  waiter.tv_sec = 0;
  waiter.tv_nsec = milliseconds * 1000;
  nanosleep(&waiter, NULL);
  return;
}

int main(int argc, char ** argv){
  uint32_t color = 0;
  uint16_t red = 0;
  uint16_t green = 0;
  uint16_t blue = 0;
  uint8_t character = 0;
  uint32_t start = 0;
  int8_t fader = 1;

  while(1){
    for(color = start; color < 0x3ff; color++){
      if (character == 70){
        printf("\r");
        delay(100);
        start++;
        color = start;
        character = 0;
      }
      red = (color & 0xff);
      if((color & 0x100) == 0x100) red = 255 - red;
      delay(100);
      BG(red,green,blue);
      FG(red,green,blue);
      printf("_");
      fflush(stdout);
      character++;
    }
    color = 0x1ff;
    start = start - 0x200;
    
  }
  printf("\x1b[0m\n");
  return 0;
}
  /*
  while(1){
    for(color = start; color < 256 ||  color == 0; color=color+ fader){
      if (character == 70){
        printf("\r");
        delay(100);
        start = start + fader;
        color = start;
        character = 0;
      }
      red = color & 0xff;
      green = (color >> 8) & 0xff;
      blue = (color >> 16) & 0xff;
      delay(100);
      BG(red,green,blue);
      FG(red,green,blue);
      printf("_");
      fflush(stdout);
      character++;
    }
    fader = fader * (-1);
    if (fader != 1) start = 255;
    else start = 1;
  }
  */
