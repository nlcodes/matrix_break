#include "../include/globals.h"

/* Shape templates 3d array */
const uint8_t SHAPES[][4][4] = {
  {
    {1,1,1,1},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  },
  {
    {1,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  },
  {
    {1,1,0,0},
    {1,1,0,0},
    {0,0,0,0},
    {0,0,0,0}
  }
};

/* Init game matrix array to host placed shapes */
uint8_t game_matrix[MATRIX_WIDTH][MATRIX_HEIGHT] = {0};

/* Create variable for game loop on/off */
int running = 1;
