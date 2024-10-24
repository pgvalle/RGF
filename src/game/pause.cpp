#include "SIC.h"

using namespace RGF;

struct Pause {
  int state = 0;
  float time = 0;
  bool show_pause_symbol = true;
};

static Pause *p = NULL;

void pause_init() {
  p = new Pause;
  // pause menu effect
  SDL_SetRenderDrawBlendMode(App::instance.renderer, SDL_BLENDMODE_BLEND);
}

void pause_quit() {
  delete p;
  p = NULL;
  // no more pause menu effect
  SDL_SetRenderDrawBlendMode(App::instance.renderer, SDL_BLENDMODE_NONE);
}

void pause_draw() {
  play_draw();

  // make the pause menu effect
  SDL_SetRenderDrawColor(App::instance.renderer, 0, 0, 0, 122);
  SDL_RenderFillRect(App::instance.renderer, NULL);

  // pause symbol blink
  if (p->show_pause_symbol)
    draw_text(FONT_ASSET, 104, 8, "||");

  // countdown to go to play screen again
  if (p->state == 1)
    draw_text(FONT_ASSET, 104, 8, "%02d", 3 - (int)p->time);
}

int pause_update(float dt) {
  switch (p->state) {
    case 0: // update time because we want text blink
      p->time += dt;
      if (p->time >= 0.5) {
        p->time = 0;
        p->show_pause_symbol = !p->show_pause_symbol;
      }
      break;
    case 1: // countdown to unpause
      p->time += dt;
      if (p->time >= 3)
        return PLAY_SCREEN;
      break;
  }

  return PAUSE_SCREEN;
}

void pause_handle_event(const SDL_Event &event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      if (!event.key.repeat && event.key.keysym.sym == SDLK_ESCAPE) {
        p->state = !p->state;
        p->time = 0;
        p->show_pause_symbol = (p->state == 1 ? false : true);
      }
      break;
  }
}
