#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <iostream>

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
    return 1;
  }

  if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) &
        (IMG_INIT_PNG | IMG_INIT_JPG))) {
      std::cerr << "SDL_image init failed: "
                << IMG_GetError() << '\n';
      return 1;
  }

  if (argc < 2) {
      std::cerr << "Usage: " << argv[0]
                << " <image-path>\n";
      return 1;
  }

  SDL_Surface* surface = IMG_Load(argv[1]);

  if (!surface) {
    std::cerr << "failed to load image: " << IMG_GetError() << '\n';
    return 1;
  }

  int width = surface->w;
  int height = surface->h;

  SDL_Window* window = SDL_CreateWindow(
    "vivy",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_SHOWN
  );

  if (!window) {
    std::cerr << "Window Creation Failed: "
              << SDL_GetError() << '\n';
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED
  );

  if (!renderer) {
      std::cerr << "Renderer Creation Failed: "
                << SDL_GetError() << '\n';
      return 1;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);  

  bool running = true;
  SDL_Event event;

  float zoom = 1.0f;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }

      if (event.type == SDL_KEYDOWN) {

          if (event.key.keysym.sym == SDLK_ESCAPE) {
              running = false;
          }

          if (event.key.keysym.sym == SDLK_EQUALS) {
              zoom += 0.1f;
          }

          if (event.key.keysym.sym == SDLK_MINUS) {
              zoom -= 0.1f;
          }

          if (zoom < 0.1f) {
              zoom = 0.1f;
          }
      }

      if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y > 0) {
            zoom += 0.1f;
        }

        if (event.wheel.y < 0) {
            zoom -= 0.1f;
        }

        if (zoom < 0.1f) {
            zoom = 0.1f;
        }
      }
    }

    SDL_Rect dstRect;

    dstRect.w = static_cast<int>(width * zoom);
    dstRect.h = static_cast<int>(height * zoom);

    dstRect.x = (width - dstRect.w) / 2;
    dstRect.y = (height - dstRect.h) / 2;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();

  return 0;
}
