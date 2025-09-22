#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class loc {
public:
	char x;
	char y;
	loc();
	loc(char x_arg, char y_arg);
};

class game_object {
public:
	loc locations[64];
	char length;
	char* color;
	char action_thresh;
	char action_meter;
	game_object();
	game_object(char x_arg, char y_arg, char* color_arg);
	virtual void run();
};

class player : public game_object {
private:
	char direction;
	char segs_to_add;
public:
	player(char x_arg, char y_arg, char* color_arg);
	void add_segs(char to_add);
	void move(char dir);
	bool is_eating_self();
	void run();
};

class mouse : public game_object {
public:
	bool is_dead = false;
	mouse(char x_arg, char y_arg, char* color_arg);
	void run();
};
#endif
