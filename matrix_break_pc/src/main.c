#include "../include/config.h"
#include "../include/globals.h"
#include "../include/shape.h"
#include "../include/render.h"
#include "../include/input.h"
#include "../include/game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <time.h>

int main() {
  /* Seed rng with current time */
  srand(time(NULL));

  /* Initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* Generate SDL window */
  SDL_Window *window = SDL_CreateWindow(
    "matrix_break",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH, WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN
  );
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderSetLogicalSize(renderer, GAME_WIDTH, GAME_HEIGHT);

  /* Create current playing shape and state variables */
  Shape *current_shape = create_shape();
  unsigned int last_drop_time = SDL_GetTicks();
  unsigned int last_move_time = SDL_GetTicks();
  const unsigned int DROP_SPEED = 500;

  /* Run game loop */
  while(running) {
    unsigned int current_time = SDL_GetTicks();

    /* Handle various user inputs */
    handle_inputs(current_shape, current_time, &last_move_time);
   
    /* Drop current shape 
     * Drop test shape to see if current shape will hit floor next drop
     * If current shape hits place it in matrix; generate new shape
     * Else keep dropping
     */
    if(current_time - last_drop_time > DROP_SPEED) {
      Shape test_shape = *current_shape;
      move_shape(&test_shape, 0, 1);

      if(scan_bottom_collision(&test_shape)) {
        place_shape(current_shape);
        free(current_shape);
        current_shape = create_shape();
      } else {
        move_shape(current_shape, 0, 1);
      }
      last_drop_time = current_time;
    }

    /* Clear window to black */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    /* Remder matrix border */
    render_border(renderer);

    /* Render matrix/matrix shapes */
    render_matrix(renderer);

    /* Render current shape */
    render_shape(renderer, current_shape);
    
    /* Present renderer */
    SDL_RenderPresent(renderer);
  } 
  
  /* Frees working shape pointer from memory */
  free(current_shape);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
