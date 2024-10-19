#include "app.h"

float x = 0, y = 0, v = 100; // demo screen context

int start(int argc, char **argv) {
  App::instance.init("Hallo", 500, 500);

  // demo screen
  App::instance.define_screen({
      []() { printf("Demo init\n"); }, // init
      []() { printf("Demo quit\n"); }, // quit
      // draw
      []() {
        SDL_SetRenderDrawColor(App::instance.renderer, 0, 0, 0, 255);
        SDL_RenderClear(App::instance.renderer);

        SDL_FRect rect = { x, y, 10, 10 };
        SDL_SetRenderDrawColor(App::instance.renderer, 255, 0, 0, 255);
        SDL_RenderFillRectF(App::instance.renderer, &rect);
      },
      // update
      [](auto events, float dt) {
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

  App::instance.loop();
  App::instance.quit();
  
  return 0;
}
