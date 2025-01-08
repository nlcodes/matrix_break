#ifndef GAME_H
#define GAME_H

#include "shape.h"

void place_shape(const shape *shape);
int scan_bottom_collision(const shape *shape);

#endif
