#pragma once

#include <SDL.h>
#include <array>
#include <vector>
#include <functional>

// Make Screen::update return this to quit the game
#define RGF_NULL_SCREEN -1

namespace RGF {

  // Good alias so that you don't need to type too much
  using EventList = std::vector<SDL_Event>;

  // A Screen is defined by a positive integer (id) and 4 functions.
  // It would be good to define the screen id just like the NULL_SCREEN constant.
  // init and quit are called when the active screen changes.
  struct Screen {
    std::function<void()> init, quit, draw;
    // Processes events and returns the id of the screen the game should go to.
    std::function<int(const EventList &, float)> update;
  };

  class App {
    private:
      std::array<Screen, RGF_MAX_SCREENS> screens;

      App() {} // You Can't instantiate a App object.

    public:
      static App instance; // Global instance of RGL_App
      SDL_Window *window;
      SDL_Renderer *renderer;

      void init(const char *title, int w, int h);
      void quit();
      void loop();

      // sid must be greater than -1 and less than RGF_MAX_SCREENS (see RGL_config.h).
      // The screen with id=0 is the starting one.
      // Calling it twice with same sid will give you an assertion error.
      void define_screen(Screen &&screen, int sid);
  };

}

