#include "../SIC.h"
//#include "UI.h"

using namespace RGF;

void play_init() {

}

void play_quit() {

}

void play_draw() {
  //ui_draw();
}

int play_update(float dt) {

  return PLAY_SCREEN;
}

void play_handle_event(const SDL_Event &event) {
  //ui_update(event);
  if (event.type == SDL_QUIT)
    App::instance.should_quit = true;
}
