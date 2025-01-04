#include "../include/game.h"
#include "../include/globals.h"

/* Floor collision detection */
int scan_bottom_collision(const Shape *shape) {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(shape->shape[i][j]) {
        int block_bottom = shape->y + ((i + 1) * BLOCK_SIZE);
        if (block_bottom >= MATRIX_HEIGHT * BLOCK_SIZE) {
          return 1;
        }
      }
    }
  }
  return 0;
}

/* Place shapes into matrix once hit detected with floor */
void place_shape(const Shape *shape) {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(shape->shape[i][j]) {
        int matrix_x = shape->x / BLOCK_SIZE + j;
        int matrix_y = shape->y / BLOCK_SIZE + i + 1;
        game_matrix[matrix_x][matrix_y] = 1;
      }
    }
  }
}
