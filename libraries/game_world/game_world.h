#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <game_object.h>
typedef char* (*tp)[8];
void game_update();
void draw(game_object *obj);
bool pressed_left();
bool pressed_right();
void controls_setup(int left_param, int right_param);
void add_obj(game_object* obj);
bool collision(game_object obj1, game_object obj2);
void placeRandomly(game_object* obj);
bool is_open(int x_arg, int y_arg);
void set_inst_num(); 
tp get_buffer();

#endif
