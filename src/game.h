#pragma once

#include <common.h>

#ifndef MAX_SCREENS
#define MAX_SCREENS 8
#endif

// return Screen::update return this to quit the game
#define NULL_SCREEN -1

/**
 * A Screen is defined by a positive integer (id) and 5 functions.
 * It would be good to define the screen id just like the NULL_SCREEN constant.
 * init and quit are called when the active screen changes.
 */
struct Screen {
  std::function<void()> init, quit, draw;
  // Process events and returns the id of the screen the game should go to.
  std::function<int(const std::vector<SDL_Event> &)> update;
};

class Game {
private:
  std::array<Screen, MAX_SCREENS> screens;

  Game() {} // You Can't instantiate a Game object.

public:
  static Game instance; // Global instance of Game
  SDL_Window *window;
  SDL_Renderer *renderer;

  void init(const char *title, int w, int h);
  void quit();
  void loop();

  /**
   * sid must be greater than -1 and less than MAX_SCREENS.
   * The screen with id=0 is the starting one.
   * Calling it twice with same sid will give you an assertion error.
   */
  void define_screen(Screen &&screen, int sid);

  void *get_globals();
  void set_globals(void *globals); 
};

