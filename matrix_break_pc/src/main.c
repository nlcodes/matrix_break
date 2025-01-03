#include "../include/shape.h"
#include "../include/config.h"
#include "../include/globals.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL.h>
#include <time.h>

/* Handle inputs function */
void handle_inputs(Shape *shape, uint32_t current_time, uint32_t *last_move_time) {
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

/* Render shape function */
void render_shape(SDL_Renderer *renderer, const Shape *shape) {
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
    
    /* Render border */ 
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
