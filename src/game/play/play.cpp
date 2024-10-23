#include "../SIC.h"
#include "ufo.h"
#include "invader.h"
//#include "UI.h"

using namespace RGF;

static UFO ufo;
static std::vector<Invader> invaders;
static int inv_i, ix, iy;

void play_init(int prev_screen) {
  for (int i = 0; i < 55; i++) { 
    int r = 4 - i / 11, c = i % 11;
    invaders.push_back(Invader(r, c));
  }
  inv_i = 0;
  ix = 2;
  iy = 0;
}

void play_quit() {

}

void play_draw() {
  SDL_SetRenderDrawColor(App::instance.renderer, 0, 0, 0, 255);
  SDL_RenderClear(App::instance.renderer);
  //ui_draw();
  ufo.draw();

  for (const auto &inv : invaders)
    inv.draw();

  //draw_text(FONT_ASSET, 0, 0, "hallo, bre");
  //draw_clip(INVADER1_ASSET, 200, 200, { 0, 0, 8, 8 });
}

int play_update(float dt) {
  ufo.update(dt);

  invaders[inv_i].move(ix, iy);
  inv_i = (inv_i + 1) % invaders.size();

  if (inv_i == 0 && iy == 0) {
    // check if got to left or right limits
    for (const auto &inv : invaders) {
      if (inv.x > 220 || inv.x < 10) {
        ix = -ix;
        iy = 8;
        break;
      }
    }
  }
  else if (inv_i == 0 && iy != 0) {
    iy = 0;
  }

  return PLAY_SCREEN;
}

void play_handle_event(const SDL_Event &event) {
  //ui_update(event);
  if (event.type == SDL_QUIT)
    App::instance.should_quit = true;
}
