#include "../../SIC.h"
#include "UFO.h"
//#include "UI.h"

using namespace RGF;

static UFO ufo;

void play_init(int prev_screen) {

}

void play_quit() {

}

void play_draw() {
  SDL_SetRenderDrawColor(App::instance.renderer, 0, 0, 0, 255);
  SDL_RenderClear(App::instance.renderer);
  //ui_draw();
  ufo.draw();
  //draw_text(FONT_ASSET, 0, 0, "hallo, bre");
  //draw_clip(INVADER1_ASSET, 200, 200, { 0, 0, 8, 8 });
}

int play_update(float dt) {
  ufo.update(dt);
  return PLAY_SCREEN;
}

void play_handle_event(const SDL_Event &event) {
  //ui_update(event);
  if (event.type == SDL_QUIT)
    App::instance.should_quit = true;
}
