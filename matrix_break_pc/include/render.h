#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "shape.h"

void render_shape(SDL_Renderer *renderer, const Shape *shape);
void render_matrix(SDL_Renderer *renderer);
void render_border(SDL_Renderer *renderer);

#endif
