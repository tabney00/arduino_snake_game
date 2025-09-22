#include <Arduino.h>
#include <refresh.h>

int last_now = millis();
int scan_checkpoint = last_now;
int curr_y = 0;

//setup all the pins to use for display
void refresh_setup() {
  for (int i = 22; i <= 53; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

//refresh the display based on what's in the buffer and
//the minimum time to wait before refreshing again
void refresh(char* buffer[8][8], int milli) {
  int now = millis();
  if (now > scan_checkpoint + milli) {   
    //kill the previous line
    setYPin(getPrevY(curr_y), LOW);

    for (int x = 0; x < 8; x++) {
      char* color = buffer[x][curr_y];
      setXPin(color, x);
      
    }
    setYPin(curr_y, HIGH);
    curr_y = getNextY(curr_y);
    scan_checkpoint = now;
  } else if (now < last_now) {
    scan_checkpoint = now;
  }
  last_now = now;
  
}

//previous line scanned
int getPrevY(int y) {
  if (y == 0) {
    return 7; 
  }
  return y - 1;
}

//next line to scan
int getNextY(int y) {
  if (y == 7) {
    return 0;
  }
  return y + 1;  
}

//which pin to set if a column in this row is to be lit
int setYPin(int y, int sig) {
  //row outputs are on even pins starting at 22 
  int yPin = -1;
  if (y <= 3) {
    yPin =  22 + 2*y;
  } else {
  //except starting from row 4, where the outputs continue on pin 46. It's just layed out that way
    yPin = 46 + 2*(y-4);
  }
  digitalWrite(yPin, sig);
}

//which pin to set if that column is to be set a color
int setXPin(char* color, int x) {
 //columns, will be different depending on the color, always odd pins
 int redPin = 23 + 2*x;
 int bluePin = 39 + 2*x;
 int greenPin = 30 + 2*(7 - x); //this one's wired weirdly
 if (!strcmp(color, "red")) {
   digitalWrite(redPin, LOW);
   digitalWrite(greenPin, HIGH);
   digitalWrite(bluePin, HIGH);
     
  } else if (!strcmp(color, "green")) {
   digitalWrite(redPin, HIGH);
   digitalWrite(greenPin, LOW);
   digitalWrite(bluePin, HIGH);
 
 } else if (!strcmp(color, "blue")) {
   digitalWrite(redPin, HIGH);
   digitalWrite(greenPin, HIGH);
   digitalWrite(bluePin, LOW);
 
 } else if (!strcmp(color, "violet")) {
   digitalWrite(redPin, LOW);
   digitalWrite(greenPin, HIGH);
   digitalWrite(bluePin, LOW);
   
 } else if (!strcmp(color, "yellow")) {
   digitalWrite(redPin, HIGH);
   digitalWrite(greenPin, LOW);
   digitalWrite(bluePin, LOW);

 } else if (!strcmp(color, "white")) {
   digitalWrite(redPin, LOW);
   digitalWrite(greenPin, LOW);
   digitalWrite(bluePin, LOW);

 } else {
   digitalWrite(redPin, HIGH);
   digitalWrite(greenPin, HIGH);
   digitalWrite(bluePin, HIGH);
 }
}
