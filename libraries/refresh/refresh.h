#ifndef REFRESH_H
#define REFRESH_H

void refresh_setup();
void refresh(char* buffer[8][8], int milli);
int getPrevY(int y);
int getNextY(int y);
int setYPin(int y, int sig);
int setXPin(char* color, int x);

#endif
