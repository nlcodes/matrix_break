#ifndef INPUT_H
#define INPUT_H

#include "shape.h"
#include <SDL2/SDL.h>
#include <stdint.h>

void handle_inputs(Shape *shape, uint32_t current_time, uint32_t *last_move_time);

#endif
