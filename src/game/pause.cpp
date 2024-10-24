#include "SIC.h"

using namespace RGF;

struct Pause {
  int state;
  float time;
  bool show_pause_symbol;
};

static Pause *p = NULL;

void pause_init() {
  p = new Pause;
  p->state = 0;
  p->time = 0;
  p->show_pause_symbol = true;
}

void pause_quit() {
  delete p;
  p = NULL;
}

void pause_draw() {
  play_draw();

  if (p->show_pause_symbol)
    draw_text(FONT_ASSET, 104, 8, "||");

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

