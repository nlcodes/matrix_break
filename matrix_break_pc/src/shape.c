#include "../include/shape.h"
#include "../include/config.h"
#include "../include/globals.h"
#include <stdlib.h>
#include <stdint.h>

/* Create shape function */
Shape *create_shape() {
  Shape *new_shape = malloc(sizeof(Shape));

  /* Init x, y, rotation */
  new_shape->x = (MATRIX_WIDTH / 2) * BLOCK_SIZE;
  new_shape->y = 0;
  new_shape->rotation = 0;

  /* Pick random shape */
  int rand_temp = rand() % 3;

  /* Copy shape data from template */
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      new_shape->shape[i][j] = SHAPES[rand_temp][i][j];
    }
  }
  return new_shape;
}

/* Move shape function */
void move_shape(Shape *shape, int dx, int dy) {
  shape->x += (dx * BLOCK_SIZE);
  shape->y += (dy * BLOCK_SIZE);
}
