// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
  SDL_Texture *texture = NULL;
  SDL_Renderer *renderer = NULL;
  char filename[256];
  if (argc < 2) {
    printf("Usage: %s filename[256]\n", args[0]);
    return -1;
  }
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }

  memmove(filename, args[1], strlen(args[1]));
  char *sep[] = {".jpg", ".png"};
  filename[strlen(args[1])] = '\0';

  if (strstr(filename, sep[0]) != NULL) {
    if (IMG_Init(IMG_INIT_JPG) == 0) {
      fprintf(stderr, "could not initialize image: %s\n", SDL_GetError());
      return 2;
    }
  } else if (strstr(filename, sep[1]) != NULL) {
    if (IMG_Init(IMG_INIT_PNG) == 0) {
      fprintf(stderr, "could not initialize image: %s\n", SDL_GetError());
      return 2;
    }
  }
  screenSurface = IMG_Load(filename);
  if (screenSurface == NULL) {
    fprintf(stderr, "Loading img failed: %s\n", SDL_GetError());
    return 5;
  }

  window = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screenSurface->w / 2,
                            screenSurface->h / 2, SDL_WINDOW_OPENGL);
  SDL_SetWindowResizable(window, 1);

  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 3;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(stderr, "Creating renderer failed: %s\n", SDL_GetError());
    return 4;
  }

  texture = SDL_CreateTextureFromSurface(renderer, screenSurface);
  if (texture == NULL) {
    fprintf(stderr, "Creating texture failed: %s\n", SDL_GetError());
    return 6;
  }

  SDL_FreeSurface(screenSurface);

  while (1) {
    SDL_Event ev;
    if (SDL_WaitEvent(&ev)) {
      if (ev.type == SDL_QUIT) {
        break;
      }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
