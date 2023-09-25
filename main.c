#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
//#define BG(r, g, b)  \x1b[48;0;r;g;bm
//#define FG(r, g, b)  \x1b[38;0;r;g;bm
#define LED_LENGTH 100
#define DELAY  delay(50);


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
  uint32_t color = 0x200;
  uint16_t red = 0;
  uint16_t green = 0;
  uint16_t blue = 0;
  uint8_t character = 0;
  uint32_t start = 0x200;
  uint8_t inc = 0;
  uint8_t dec = 0;
  uint8_t status = 0;
  
  while(1){
    for(color = start; start < 0x6ff; color = color+4){
      if (character == LED_LENGTH){
        printf("\r");
        DELAY;
        start = start + 5;
        color = start;
        character = 0;
      }
      inc  = (color & 0xff);
      dec = 255 - inc;
      status = color >> 8;
      switch(status){
        case 2: {
          red = 255;
          blue = 0;
          green = inc;
          break;
        }
        case 3: {
          red = dec;
          blue = 0;
          green = 255;
          break;
        }
        case 4: {
          red = 0;
          blue = inc;
          green = 255;
          break;
        }
        case 5: { 
          red = 0;
          blue = 255;
          green = dec;
          break;
        }
        case 6: {
          red = inc;
          blue = 255;
          green = 0;
          break;
        }
        case 7: {
          red = 255;
          blue = dec;
          green = 0;
          break;
        }
        case 8: {
          red = 255;
          blue = 0;
          green = inc;
          break;
        }
        case 1: {
          red = 255;
          blue = dec;
          green = 0;
          break;
        }
        case 0: {
          red = inc;
          blue = 255;
          green = 0;
          break;
        }

        default: {
          printf("\x1b[0m\nerror: status is %d", status);
          return -1;
        }
      }
      DELAY;
      BG(red,green,blue);
      FG(red,green,blue);
      printf("_");
      fflush(stdout);
      character++;
    }
    //printf("\x1b[0m\nFinished. Color = 0x%x, Start = 0x%x", color, start);
    start = start - 0x600;
    
  }
  printf("\x1b[0m\n");
  return 0;
}

