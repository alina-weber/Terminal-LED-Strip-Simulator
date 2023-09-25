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
  waiter.tv_nsec = milliseconds * 5000;
  nanosleep(&waiter, NULL);
  return;
}

int main(int argc, char ** argv){
  uint32_t color = 0;
  uint16_t red = 0;
  uint16_t green = 0;
  uint16_t blue = 0;
  uint8_t character = 0;
  uint8_t start = 1;
  int8_t fader = 1;
  while(1){
    for(color = start; color < 256 && color > 0; color++){
      if (character >= 70){
        printf("\r");
        fflush(stdout);
        delay(100);
        start = start + fader;
        color = start;
        character = 0;
        continue;
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
    if (start == 0 || start > 185) start = 1;
    else start = 185;
    character = 0;
    printf("\r");
  }
  printf("\x1b[0m\n");
  return 0;
}

