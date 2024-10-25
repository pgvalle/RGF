#include "SIC.h"
#include <string>
#include <cctype>

using namespace RGF;

struct Splash {
  std::string text =
      "         PLAY\n\n\n"
      "    SPACE INVADERS\n\n\n\n"
      "*SCORE ADVANCES TABLE*\n\n"
      "       =? MYSTERY\n\n"
      "       =30 POINTS\n\n"
      "       =20 POINTS\n\n"
      "       =10 POINTS";
  
  int state = 0, i = 0;
  float time = 0;
};

static Splash *s = NULL;

void splash_init() {
  s = new Splash;
}

void splash_quit() {
  delete s;
  s = NULL;
}

void splash_draw() {
  SDL_SetRenderDrawColor(App::instance.renderer, 0, 0, 0, 255);
  SDL_RenderClear(App::instance.renderer);

  draw_text(FONT_ASSET, 24, 64, s->text.substr(0, s->i).c_str());

  if (s->i <= s->text.find('*'))
    return;

  draw_clip(UFO_ASSET, 59, 136, { 0, 0, 24, 8 });
  draw_clip(INVADER1_ASSET, 67, 152, { 0, 0, 8, 8 });
  draw_clip(INVADER2_ASSET, 66, 168, { 0, 0, 11, 8 });
  draw_clip(INVADER3_ASSET, 65, 184, { 0, 0, 12, 8 });
}

///////////////////////////////////////////////////////////

void update_text_display(float dt) {
  // draw one more character each 4 ticks
  s->time += dt;
  if (s->time < 0.1)
    return;

  s->time = 0;

  // skip whitespaces and new lines
  do s->i++;
  while (s->i < s->text.length() && s->text[s->i] <= ' ');
}

int splash_update(float dt) {
  switch (s->state) {
    case -1: // go to play screen
      return PLAY_SCREEN;
    case 0: // wait 1.5 seconds before start displaying text
      s->time += dt;
      if (s->time >= 1.5) {
        s->state = 1;
        s->time = 0;
      }
      break;
    case 1: // typewrite a part of the text
      update_text_display(dt);
      if (s->i == s->text.find('*')) {
        s->state = 2;
        s->time = 0;
        s->i--;
      }
      break;
    case 2: // wait 2 seconds
      s->time += dt;
      if (s->time >= 2) {
        s->state = 3;
        s->time = 0;
        s->i += 23;
      }
      break;
    case 3: // typewrite remaining text
      update_text_display(dt);
      if (s->i == s->text.length())
        s->state = 4;
      break;
  }

  return SPLASH_SCREEN;
}

void splash_handle_event(const SDL_Event &event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_RETURN: // skip text typewriting or go to play state
          s->state = (s->state == 4 ? -1 : 4);
          s->i = s->text.length();
          break;
        case SDLK_q: // exit
          App::instance.should_quit = true;
          break;
      }
      break;
    case SDL_QUIT:
      App::instance.should_quit = true;
      break;
  }
}
