#include "SIC.h"

using namespace RGF;

SICGlobals sic = {
  0, 0, 0
};

int RGF_main(int argc, char **argv) {
  App::instance.init("Demo", WIDTH, HEIGHT);

  ResMan::instance.load_font(FONT_ASSET, 8, TTF_STYLE_NORMAL, "res/font.ttf");

  ResMan::instance.load_texture(CANNON_ASSET, "res/img/cannon.png");
  ResMan::instance.load_texture(INVADER1_ASSET, "res/img/invader1.png");
  ResMan::instance.load_texture(INVADER2_ASSET, "res/img/invader2.png");
  ResMan::instance.load_texture(INVADER3_ASSET, "res/img/invader3.png");
  ResMan::instance.load_texture(INVADER_DEATH_ASSET, "res/img/invaderdeath.png");
  ResMan::instance.load_texture(UFO_ASSET, "res/img/ufo.png");

  //App::instance.define_screen({
  //    splash_init,
  //    splash_quit,
  //    splash_draw,
  //    splash_update }, SPLASH_SCREEN);

  App::instance.define_screen({
    play_init,
    play_quit,
    play_draw,
    play_update,
    play_handle_event }, PLAY_SCREEN);

  App::instance.loop();
  App::instance.quit();
  
  return 0;
}
