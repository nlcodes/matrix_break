#ifndef GAME_H
#define GAME_H

#include "shape.h"

void place_shape(const Shape *shape);
int scan_bottom_collision(const Shape *shape);

#endif
