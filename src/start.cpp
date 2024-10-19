#include "game.h"

float x = 0, y = 0, v = 100; // example screen stuff

int start(int argc, char **argv) {
  Game::instance.init("Hallo", 500, 500);

  // example screen here
  Game::instance.define_screen({
      []() {}, // init
      []() {}, // quit
      []() {   // draw
        SDL_SetRenderDrawColor(Game::instance.renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::instance.renderer);

        SDL_FRect rect = { x, y, 10, 10 };
        SDL_SetRenderDrawColor(Game::instance.renderer, 255, 0, 0, 255);
        SDL_RenderFillRectF(Game::instance.renderer, &rect);
      },
      [](auto events, float dt) { // update
        for (const auto &event : events) {
          if (event.type == SDL_QUIT)
            return NULL_SCREEN;
        }

        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        float d = v * dt;

        if (keys[SDL_SCANCODE_A])
          x -= d;
        if (keys[SDL_SCANCODE_D])
          x += d;
        if (keys[SDL_SCANCODE_W])
          y -= d;
        if (keys[SDL_SCANCODE_S])
          y += d;

        return 0;
      }}, 0);

  Game::instance.loop();
  Game::instance.quit();
  
  return 0;
}
