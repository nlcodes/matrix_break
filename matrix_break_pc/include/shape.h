#ifndef SHAPE_H
#define SHAPE_H

#include "config.h"
#include <stdint.h>

/* Shapes and rotation state */
typedef struct {
  uint8_t shape[BLOCK_SIZE][BLOCK_SIZE];
  int x, y;
  int rotation;
} shape;

shape *create_shape();
void move_shape(shape *shape, int dx, int dy);

#endif
