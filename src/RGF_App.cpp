#include "RGF_App.h"
#include "RGF_ResMan.h"

using namespace RGF;

void App::init(const char *title, int w, int h) {
  window = SDL_CreateWindow(
      title,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      w,
      h,
      SDL_WINDOW_RESIZABLE);
  SDL_assert(window);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_assert(renderer);

  screens.fill({ NULL, NULL, NULL, NULL }); // zero-initialize all screens

  SDL_RenderSetLogicalSize(renderer, w, h);
}

void App::quit() {
  ResMan::instance.free_everything();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void App::loop() {
  Uint32 tpf = 1000 / RGF_FRAMERATE, delta = 1; // time per frame and time of frame
  int sid = 0, new_sid = 0; // screen index and new screen index

  screens[sid].init();

  while (new_sid != RGF_NULL_SCREEN) {
    std::vector<SDL_Event> events;
    SDL_Event event;
    Uint32 start = SDL_GetTicks();

    // if screen changed, initialize new screen and quit current
    if (sid != new_sid) {
      SDL_assert(new_sid >= 0 && new_sid < RGF_MAX_SCREENS); // sid within range
      // the new screen must be a valid one
      SDL_assert(screens[new_sid].init && screens[new_sid].quit &&
          screens[new_sid].draw && screens[new_sid].update);

      screens[sid].quit();
      sid = new_sid;
      screens[sid].init();
    }
 
    // event querying
    while (SDL_PollEvent(&event))
      events.push_back(event);

    // state update
    new_sid = screens[sid].update(events, 1e-3 * delta);

    // rendering
    screens[sid].draw();
    SDL_RenderPresent(renderer);

    // fps control
    delta = SDL_GetTicks() - start;
    if (delta < tpf) {
      SDL_Delay(tpf - delta);
      delta = tpf;
    }
  }

  screens[sid].quit();
}

void App::define_screen(Screen &&screen, int sid) {
  SDL_assert(sid >= 0 && sid < RGF_MAX_SCREENS); // sid within range
  // don't override already defined screens
  SDL_assert(!screens[sid].init && !screens[sid].quit &&
      !screens[sid].draw && !screens[sid].update);

  screens[sid] = screen;
}

void *App::get_globals() {
  return SDL_GetWindowData(window, "globals");
}

void App::set_globals(void *globals) {
  SDL_SetWindowData(window, "globals", globals);
}

App App::instance;

