#ifndef _MENUS_H
#define _MENUS_H

#include "enums.h"

extern light_type currently_adjusting_light;
extern double *targetRed, *targetGreen, *targetBlue;
extern color adjusting_color;
extern game_state current_state;

void display2D();

#endif