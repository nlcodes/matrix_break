#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

/* Define dimensions rotated from OLED */
#define GAME_WIDTH 64
#define GAME_HEIGHT 128
#define WINDOW_WIDTH 128
#define WINDOW_HEIGHT 258

/* Gameplay matrix units in blocks; define block size in px */
#define MATRIX_WIDTH 15
#define MATRIX_HEIGHT 24
#define BLOCK_SIZE 4

int main() {
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

  int running = 1;
  SDL_Event event;

  /* Run game loop */
  while(running) {
    /* Poll for quit event */
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }

    /* Clear window to black */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    /* Render border */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect outer_border = { 0, 0, 64, MATRIX_HEIGHT * BLOCK_SIZE + 4 };
    SDL_RenderDrawRect(renderer, &outer_border);
    SDL_Rect inner_border = { 1, 1, 62, MATRIX_HEIGHT * BLOCK_SIZE + 2 };
    SDL_RenderDrawRect(renderer, &inner_border);

    /* Render block: x, y, width, height */
    SDL_Rect block = {
      30, 
      6,
      4,  
      4 
    };
    SDL_RenderFillRect(renderer, &block);

    /* Present renderer */
    SDL_RenderPresent(renderer);
  } 
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
