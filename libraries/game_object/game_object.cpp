#include <Arduino.h>
#include <game_object.h>
#include <game_world.h>

game_object::game_object(char x_arg, char y_arg, char* color_arg)
: length(0), color((char*)"off"), action_thresh(10), action_meter(0) {
	locations[0].x = x_arg;
	locations[0].y = y_arg;
	length = 1;
	color = color_arg;
}

game_object::game_object() 
: length(0), color((char*)"off"){}

void game_object::run(){}

player::player(char x_arg, char y_arg, char* color_arg)
	: direction(1), segs_to_add(0), game_object(x_arg, y_arg, color_arg) {}
	
void player::add_segs(char to_add) {
	segs_to_add += to_add;
}

void player::move(char dir) {
	if (segs_to_add > 0) {
		length++;
		segs_to_add--;
	}
	bool advanced = false;
	char newX = locations[0].x;
	char newY = locations[0].y;
	switch(dir) {
		case 0:
			if (locations[0].y > 0) {
				newY = locations[0].y - 1;
				advanced = true;
			}
			break;
		case 1:
			if (locations[0].x < 7) {
				newX = locations[0].x + 1;
				advanced = true;			
			}
			break;
		case 2:
			if (locations[0].y < 7) {
				newY = locations[0].y + 1;
				advanced = true;			
			}
			break;
		case 3:
			if (locations[0].x > 0) {
				newX = locations[0].x - 1;
				advanced = true;			
			}
			break;
	}
	for (int i = length - 1; i >= 1 && advanced; i--) {
		locations[i] = locations[i-1];
	}
	locations[0].x = newX;
	locations[0].y = newY;
}

void player::run() {
	if (pressed_right()) {
		if (direction >= 3) {
			direction = 0;
		} else {
			direction++;
		}
	} else if (pressed_left()) {
		if (direction <= 0) {
			direction = 3;
		} else {
			direction--;
		}
	}
	action_meter++;
	if (action_meter<action_thresh) {
		return;
	}
	action_meter = 0;
	move(direction);
}

bool player::is_eating_self() {
	for (int i = 1; i < length; i++) {
		if (locations[0].x == locations[i].x
			&& locations[0].y == locations[i].y) {
			return true;
		} 		
	}
	return false;
}

loc::loc(char x_arg, char y_arg)
: x(0), y(0) {
	x = x_arg;
	y = y_arg;
}

loc::loc()
: x(0), y(0) {}