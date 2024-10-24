#include "../SIC.h"
#include "ufo.h"
#include "horde.h"

using namespace RGF;

struct Play {
  int state = 0;
  float time = 0;
  UFO ufo;
  Horde horde;
};

static Play *p = NULL;

void play_init() {
  // game being started over again. It was not paused
  if (!p)
    p = new Play;
  else
    p->state = p->state + RGF_MAX_SCREENS; // restore exact same state before pausing
}

void play_quit() {
  // Game paused. Do not dealocate play screen data.
  if (p->state < 0)
    return;

  delete p;
  p = NULL;
}

void play_draw() {
  SDL_SetRenderDrawColor(App::instance.renderer, 0, 0, 0, 255);
  SDL_RenderClear(App::instance.renderer);

  //ui_draw();
  p->ufo.draw();
  p->horde.draw();

  //draw_text(FONT_ASSET, 0, 0, "hallo, bre");
  //draw_clip(INVADER1_ASSET, 200, 200, { 0, 0, 8, 8 });
}

int play_update(float dt) {
  if (p->state < 0)
    return PAUSE_SCREEN;

  switch (p->state) {
    case 0: // populating horde
      p->horde.populate();
      p->state = (p->horde.invaders.size() < 55 ? 0 : 1);
      break;
    case 1: // wait before showing cannon and make it controllable
      p->ufo.update(dt);
      p->horde.move();
      p->time += dt;
      if (dt >= 1) {
        p->state = 2;
        p->time = 0;
      }
      break;
    case 2: // player playing
      p->ufo.update(dt);
      p->horde.move();
      break;
  }

  return PLAY_SCREEN;
}

void play_handle_event(const SDL_Event &event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      if (!event.key.repeat && event.key.keysym.sym == SDLK_p)
        p->state = p->state - RGF_MAX_SCREENS; // so that we know what state we were
      break;
    case SDL_QUIT:
      App::instance.should_quit = true;
      break;
    default:
      // ...
      break;
  }
}
