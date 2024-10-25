#include "../SIC.h"
#include "ufo.h"
#include "horde.h"
#include "cannon.h"

using namespace RGF;

struct Play {
  int state = 0;
  float time = 0;
  int lives = 3;
  UFO ufo;
  Horde horde;
  Cannon cannon;
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

  p->ufo.draw();
  p->horde.draw();
  p->cannon.draw();

  draw_text(FONT_ASSET, 8, 240, "%d", p->lives);
  for (int i = 0; i < p->lives - 1; i++) {
    draw_clip(CANNON_ASSET, 24 + 16 * i, 240, { 0, 0, 16, 8 });
  }
}

int play_update(float dt) {
  if (p->state < 0)
    return PAUSE_SCREEN;

  const Uint8 *keys = SDL_GetKeyboardState(NULL);
  int cannon_dx = 0;

  cannon_dx -= keys[SDL_SCANCODE_A];
  cannon_dx += keys[SDL_SCANCODE_D];
  p->cannon.vx = 80 * cannon_dx;

  switch (p->state) {
    case 0: // populating horde
      p->horde.populate();
      p->state = (p->horde.invaders.size() < 55 ? 0 : 1);
      break;
    case 1: // wait before showing cannon and make it controllable
      p->horde.move();
      p->cannon.update(dt);
      if (p->cannon.state == Cannon::ALIVE)
        p->state = 2;
      break;
    case 2: // player playing
      p->ufo.update(dt);
      p->horde.move();
      p->cannon.update(dt);

      // TODO: check collisions with cannon before

      if (p->cannon.state == Cannon::DYING)
        p->state = 3;
      break;
    case 3: // player dying. Not updating anything until it alives again
      p->cannon.update(dt);
      if (p->cannon.state == Cannon::DEAD) {
        if (--p->lives == 0) // sheeesh game over
          return 0;
        p->state = 4;
      }
      break;
    case 4: // player dead
      p->cannon.update(dt);
      if (p->cannon.state == Cannon::DEAD)
        p->state = 1;
      break;
  }

  return PLAY_SCREEN;
}

void play_handle_event(const SDL_Event &event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
        case SDLK_ESCAPE:
          p->state = p->state - RGF_MAX_SCREENS; // so that we know what state we were
          break;
        case SDLK_q:
          App::instance.should_quit = true;
          break;
        case SDLK_e:
          if (p->state != 2) // only trigger test in playing state
            break;
          p->cannon.state = Cannon::DYING;
          p->cannon.time1 = 0; // time1 for death time
          p->cannon.time2 = 0;
          break;
      }
      break;
    case SDL_QUIT:
      App::instance.should_quit = true;
      break;
    default:
      // ...
      break;
  }
}
