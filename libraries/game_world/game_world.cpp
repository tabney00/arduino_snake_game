#include <Arduino.h>
#include <game_world.h>
#include <game_object.h>

char* world_buffer[8][8];
game_object* instances[10];
char inst_num = 0;

int left_butt = -1;
int right_butt = -1;

int left_state = HIGH;
int right_state = HIGH;

void game_update() {
	for (int j = 0; j < 8; j++) {
		for (int k = 0; k < 8; k++) {
			world_buffer[j][k] = (char*)"off";
		}
	}
	for (int i = 0; i < inst_num; i++) {
		instances[i]->run();
		draw((instances[i]));
	}
  
}

void draw(game_object *obj) {
	for (int i = 0; i < obj->length; i++) {
		world_buffer[(obj->locations[i]).x][(obj->locations[i]).y] = obj->color;
	}
}

bool pressed_left() {
	if (digitalRead(left_butt) == HIGH) {
		left_state = HIGH;
		return false;
	} else if (left_state == HIGH) {
		left_state = LOW;
		return true;
	} else {
		return false;
	}
}

bool pressed_right() {
	if (digitalRead(right_butt) == HIGH) {
		right_state = HIGH;
		return false;
	} else if (right_state == HIGH) {
		right_state = LOW;
		return true;
	} else {
		return false;
	}
}

void controls_setup(int left_param, int right_param) {
	left_butt = left_param;
	right_butt = right_param;
	pinMode(left_param, INPUT_PULLUP);
	pinMode(right_param, INPUT_PULLUP);
}

void add_obj(game_object* obj) {
	instances[inst_num] = obj;
	inst_num++;
}

bool collision(game_object obj1, game_object obj2) {
	if (obj1.locations[0].x == obj2.locations[0].x
		&& obj1.locations[0].y == obj2.locations[0].y) {
		return true;
	} else {
		return false;
	}
}

void placeRandomly(game_object* obj) {
	int rx = random() % 8;
	int ry = random() % 8;
	while (!is_open(rx, ry)) {
		rx = random() % 8;
		ry = random() % 8;	
	}
	obj->locations[0].x = rx;
	obj->locations[0].y = ry;
}

bool is_open(int x_arg, int y_arg) {
	game_object* player = instances[0];
	for (int i = 0; i < player->length; i++) {
		if (player->locations[i].x == x_arg && player->locations[i].y == y_arg) {
			return false;
		}
	}
	return true;
}

void set_inst_num(char num) {
	inst_num = num;
}

tp get_buffer() {
	return world_buffer;
}