#include "../include/input.h"
#include "../include/globals.h"

/* Handle inputs function */
void handle_inputs(shape *shape, uint32_t current_time, uint32_t *last_move_time) {
  SDL_Event event;

  /* Poll for events */
  while (SDL_PollEvent(&event)) {
    /* Look for quit event */
    if (event.type == SDL_QUIT) running = 0;

    /* Look for x axis movement inputs; call move shape */
    static int key_held = 0;

    if (event.type == SDL_KEYUP) key_held = 0;
    if (event.type == SDL_KEYDOWN) {
      if (!key_held && current_time - *last_move_time > 150) {
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT && shape->x > BLOCK_SIZE) {
          move_shape(shape, -1, 0);
          *last_move_time = current_time;
        }
        /* Fix right wall detection */
        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
          move_shape(shape, 1, 0);
          *last_move_time = current_time;
        }
        key_held = 1;
      }
    }
  }
}
