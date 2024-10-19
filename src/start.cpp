#include "game.h"

int x = 0, y = 0; // example screen rect pos

int start(int argc, char **argv) {
  Game::instance.init("Hallo", 500, 500);

  // example screen here
  Game::instance.define_screen({
      []() {}, // init
      []() {}, // quit
      []() {   // draw
        SDL_SetRenderDrawColor(Game::instance.renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::instance.renderer);

        SDL_Rect rect = {x, y, 40, 40};
        SDL_SetRenderDrawColor(Game::instance.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Game::instance.renderer, &rect);
      },
      [](const SDL_Event &event) { // update
        if (event.type == SDL_QUIT)
          return NULL_SCREEN;

        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        if (keys[SDLK_a])
          x -= 2;
        if (keys[SDLK_d])
          x += 2;
        if (keys[SDLK_w])
          y -= 2;
        if (keys[SDLK_s])
          y += 2;

        return 0;
      }}, 0);

  Game::instance.loop();
  Game::instance.quit();
  
  return 0;
}
