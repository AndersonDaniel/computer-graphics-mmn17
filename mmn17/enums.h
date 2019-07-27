#ifndef _ENUMS_H
#define _ENUMS_H

enum game_state {
	playing,
	help,
	adjust_light,
	adjust_camera
};

enum color {
	red, green, blue
};

enum light_type {
	ambient,
	diffuse
};


#endif