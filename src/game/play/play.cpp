#include "../SIC.h"
#include "ufo.h"
#include "horde.h"
//#include "UI.h"

using namespace RGF;

static int state;
static float time;
static UFO ufo;
static Horde horde;

void play_init(int prev_screen) {
  state = 0;
  time = 0;
}

void play_quit() {

}

void play_draw() {
  SDL_SetRenderDrawColor(App::instance.renderer, 0, 0, 0, 255);
  SDL_RenderClear(App::instance.renderer);

  //ui_draw();
  ufo.draw();
  horde.draw();

  //draw_text(FONT_ASSET, 0, 0, "hallo, bre");
  //draw_clip(INVADER1_ASSET, 200, 200, { 0, 0, 8, 8 });
}

int play_update(float dt) {
  switch (state) {
    case 0: // populating horde
      horde.populate();
      state = (horde.invaders.size() < 55 ? 0 : 1);
      break;
    case 1: // wait before showing player and make it controllable
      ufo.update(dt);
      horde.move();
      time += dt;
      if (dt >= 1) {
        state = 2;
        time = 0;
      }
      break;
    case 2: // player playing
      ufo.update(dt);
      horde.move();
      break;
  }

  return PLAY_SCREEN;
}

void play_handle_event(const SDL_Event &event) {
  //ui_update(event);
  if (event.type == SDL_QUIT)
    App::instance.should_quit = true;
}
