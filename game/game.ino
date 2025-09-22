#include <animations.h>
#include <game_object.h>
#include <game_world.h>
#include <refresh.h>
#include <stdlib.h>
#include <string.h>

int last_now_m = millis();
int logicCheckpoint = last_now_m;
char* buffer[8][8];
int left = 2;
int right = 3;
player p1 = player(1,1, (char*)"green");
game_object mouse = game_object(4, 4, (char*)"blue");
bool game_over = false;
char ROUND_MAX = 125;
char animation_rounds = 0;
char animation_stage = 0;
bool win = false;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  controls_setup(left, right);
  refresh_setup();
  randomSeed(analogRead(A0));
  add_obj(&p1);
  add_obj(&mouse);

  
}
//
// the loop routine runs over and over again forever:
void loop() {
  int now = millis();
  if (now > logicCheckpoint + 16) {
      snake(get_buffer(), (char*)"red", (char*)"green");       
    if (!game_over) {
      game_update(); 
      if (collision(p1, mouse)) {
        p1.add_segs(1);
        placeRandomly(&mouse);
      }
      if (p1.is_eating_self() || is_out_of_bounds(p1)) {
        p1.color = (char*)"red";
        p1.is_dead = true;
        game_over = true;
      }

      if (p1.length == 64) {
        win = true;
        p1.is_dead = true;
        game_over = true;
      }
    
    } else {
      animation_rounds++;
      if (animation_stage == 0) {
        game_update(); 
        if (animation_rounds > ROUND_MAX) {
          clear_buffer();
          animation_rounds = 0;
          animation_stage = 1;
        }
      } else {
        if (win) {
          sparkle(get_buffer());
        } else {
          snake(get_buffer(), (char*)"red", (char*)"green");          
        }
        if (animation_rounds > ROUND_MAX) {
          animation_reset();
          animation_rounds = 0;
          animation_stage = 0;
          game_over = false;
          win = false;
          p1 = player(1,1, (char*)"green");
          mouse = game_object(4, 4, (char*)"blue");
        }
      }
    }
    logicCheckpoint = now;
  
  } else if (now < last_now_m) {
    logicCheckpoint = now;  
  }
  refresh(get_buffer(), 1);
  last_now_m = now;
}
