#include "../SIC.h"
#include <string>

using namespace RGF;

static std::string text =
"         PLAY\n\n\n"
"    SPACE INVADERS\n\n\n\n"
"*SCORE ADVANCES TABLE*\n\n"
"       =? MYSTERY\n\n"
"       =30 POINTS\n\n"
"       =20 POINTS\n\n"
"       =10 POINTS";

static int state, ticks, i;

///////////////////////////////////////////////////////////

void splash_init() {
  state = 0;
  ticks = 0;
  i = 0;
}

void splash_quit() {

}

///////////////////////////////////////////////////////////

void splash_draw() {
  //ui_draw();

  FC_Draw(
      ResMan::instance.get_font(FONT_ASSET),
      App::instance.renderer,
      24,
      64,
      text.substr(0, i).c_str());
  //sic.draw_text(104, 8, "||");
  
  if (i <= text.find('*'))
    return;

  //sic.draw_clip({ 0, 0, 16, 8 }, { 64, 136, 16, 8 });
  //sic.draw_clip({ 0, 16, 8, 8 }, { 68, 152, 8, 8 });
  //sic.draw_clip({ 0, 24, 11, 8 }, { 66, 168, 11, 8 });
  //sic.draw_clip({ 0, 32, 12, 8 }, { 66, 184, 12, 8 });
}

///////////////////////////////////////////////////////////

void update_text_display() {
  // draw one more character each 4 ticks
  if (ticks++ % 3)
    return;

  // skip whitespaces and new lines
  do i++;
  while (i < text.length() && (text[i] == ' ' || text[i] == '\n'));
}

int splash_update(const EventList &events, float dt) {
  //ui_update(event);

  for (const auto& event : events) {
    if (event.type == SDL_KEYDOWN && !event.key.repeat) {
      SDL_Keycode key = event.key.keysym.sym;

      if (key == SDLK_q)
        App::instance.should_quit = true;
      
      if (key == SDLK_SPACE) {
        state = 4;
        ticks = 0;
        i = text.length();
      }
    }
  }

  switch (state) {
    case 0: // wait 1.5 seconds before start displaying text
      if (ticks++ == 90)
        state = 1;
      break;
    case 1: // typewrite a part of the text
      update_text_display();
      if (i == text.find('*')) {
        state = 2;
        ticks = 0;
        i--;
      }
      break;
    case 2: // wait 1 seconds
      if (ticks++ == 60) {
        state = 3;
        i += 23;
      }
      break;
    case 3: // typewrite remaining text
      update_text_display();
      if (i == text.length())
        state = 4;
      break;
  }

  if (sic.credits)
    return 0;
  
  return SPLASH_SCREEN;
}
