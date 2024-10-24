#pragma once

#include <SDL.h>
#include <array>
#include <vector>
#include <functional>

namespace RGF {

  class App {
    public:
      // A Screen is defined by a positive integer (id) and 5 functions.
      // It would be good to define the screen id just like the NULL_SCREEN constant.
      // init and quit are called when the active screen changes.
      struct Screen {
        std::function<void()> init, quit, draw;
        // Returns the id of the screen the game should go to.
        // Receives as argument the time passed since last call.
        std::function<int(float)> update;
        std::function<void(const SDL_Event &)> handle_event;
      };

    private:
      std::array<Screen, RGF_MAX_SCREENS> screens;

      App() {} // You Can't instantiate a App object.

    public:
      static App instance; // Global instance of App

      SDL_Window *window;
      SDL_Renderer *renderer;
      bool should_quit; // quit the game inside a screen using this variable

      void init(const char *title, int w, int h);
      void quit();
      void loop();

      // sid must be greater than -1 and less than RGF_MAX_SCREENS.
      // The screen with id=0 is the starting one.
      // Calling it twice with same sid will give you an assertion error.
      void define_screen(Screen &&screen, int sid);
  };

}

