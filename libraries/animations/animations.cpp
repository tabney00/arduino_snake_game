#include "animations.h"
#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

int snkX = 0;
int snkY = 0;
int snkBound = 7;
//0 = top, 1 = right, 2 = bottom, 3 = left
int snkState = 0;
int curr_color = 0;
int rand_is_seeded = 0;

//makes smaller and smaller loops around the display in alternating colors
void snake(char* buffer[8][8], char* color0, char* color1) {
  char* use_color = color0;
  if (curr_color) {
    use_color = color1;
  }
  if (snkState == 0) {
    buffer[snkX][snkY] = use_color;
    snkX += 1;
    if (snkX > snkBound) {
      snkX -= 1;
      snkY += 1;
      snkState = 1;
    }    
  } else if (snkState == 1) {
    buffer[snkX][snkY] = use_color;
    snkY += 1;
    if (snkY > snkBound) {
      snkY -= 1;
      snkX -= 1;
      snkState = 2;  
    }
  } else if (snkState == 2) {
    if (curr_color) {
        buffer[snkX][snkY] = color1;
    } else {
        buffer[snkX][snkY] = color0;
    }
    snkX -= 1;
    if (snkX < 8 - snkBound - 1) {
      snkX += 1;
      snkY -= 1;
      snkState = 3; 
    }
   
  } else if (snkState == 3) {
    buffer[snkX][snkY] = use_color;
    snkY -= 1;
    if (snkY < 8 - snkBound) {
      snkX += 1;
      snkY += 1;
      snkBound -= 1;
      if (snkBound < 4) {
        snkState = -1;  
      } else {
        snkState = 0;  
      }
    } 
  } else if (snkState == -1) {
    snkX = 0;
    snkY = 0;
    snkBound = 7;
    if (curr_color) {
      curr_color = 0;  
    } else {
      curr_color = 1;
    }  
    snkState = 0;
  } 
}

//random flashing of every pixel
void sparkle(char* buffer[8][8]) {
  if (!rand_is_seeded) {
    srand(millis());
    rand_is_seeded = 1;  
  }
  int x;
  for (x = 0; x < 8; x++) {
    int y;    
    for (y = 0; y < 8; y++) {
       int state = rand() % 4;
       if (state == 0) {
         buffer[x][y] = "red";  
       } else if (state == 1) {
         buffer[x][y] = "green";  
       } else if (state == 2) {
         buffer[x][y] = "blue";  
       } else {
         buffer[x][y] = "off";  
       }
    }
  }  
}

//a solid color for the display
void solid(char* buffer[8][8], char* color) {
  int x;
  for (x = 0; x < 8; x++) {
    int y;    
    for (y = 0; y < 8; y++) {
        buffer[x][y] = color;   
    }
  }  
}
