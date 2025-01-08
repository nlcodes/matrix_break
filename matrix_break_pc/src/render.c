#include "../include/render.h"
#include "../include/config.h"
#include "../include/globals.h"

/* Render shape function */
void render_shape(SDL_Renderer *renderer, const shape *shape) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(shape->shape[i][j]) {
        SDL_Rect block = {
          shape->x + (j * BLOCK_SIZE),
          shape->y + (i * BLOCK_SIZE),
          BLOCK_SIZE,
          BLOCK_SIZE
        };
        SDL_RenderFillRect(renderer, &block);
      }
    }
  }
}

/* Render matrix and placed matrix shapes */
void render_matrix(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for(int i = 0; i < MATRIX_WIDTH; i++) {
    for(int j = 0; j < MATRIX_HEIGHT; j++) {
      if(game_matrix[i][j]) {
        SDL_Rect block = {
          i * BLOCK_SIZE,
          j * BLOCK_SIZE,
          BLOCK_SIZE,
          BLOCK_SIZE
        };
        SDL_RenderFillRect(renderer, &block);
      }
    }
  }
}

/* Render border */ 
void render_border(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  /* Left border */
  SDL_Rect left_border = {
    0,
    0,
    BLOCK_SIZE,
    MATRIX_HEIGHT * BLOCK_SIZE
  };
  SDL_RenderFillRect(renderer, &left_border);

  /* Right border */
  SDL_Rect right_border = {
    MATRIX_WIDTH * BLOCK_SIZE,
    0,
    BLOCK_SIZE,
    MATRIX_HEIGHT * BLOCK_SIZE
  };
  SDL_RenderFillRect(renderer, &right_border);

  /* Bottom border */
  SDL_Rect bottom_border = {
    0,
    MATRIX_HEIGHT * BLOCK_SIZE,
    (MATRIX_WIDTH + 1) * BLOCK_SIZE,
    BLOCK_SIZE 
  };
  SDL_RenderFillRect(renderer, &bottom_border);
}
