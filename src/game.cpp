#include "game.h"

void Game::init(const char *title, int w, int h) {
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
}

void Game::quit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Game::loop() {
  Uint32 tpf = 1000 / 60; // time per frame
  int sid = 0, new_sid = 0; // screen index and new screen index

  while (new_sid != NULL_SCREEN) {
    std::vector<SDL_Event> events;
    Uint32 start = SDL_GetTicks(), delta = 0;

    // if screen changed, initialize new screen and quit current
    if (sid != new_sid) {
      SDL_assert(new_sid >= 0 && new_sid < MAX_SCREENS); // sid within range
      // all functions of the new screen must be valid
      SDL_assert(screens[new_sid].init && screens[new_sid].quit &&
          screens[new_sid].draw && screens[new_sid].update);

      screens[sid].quit();
      sid = new_sid;
      screens[sid].init();
    }

    // event processing
    SDL_Event event;
    while (SDL_PollEvent(&event))
      events.push_back(event);

    new_sid = screens[sid].update(events);

    // rendering
    screens[sid].draw();
    SDL_RenderPresent(renderer);

    // fps control
    delta = SDL_GetTicks() - start;
    if (delta < tpf)
      SDL_Delay(tpf - delta);
  }
}

void Game::define_screen(Screen &&screen, int sid) {
  SDL_assert(sid >= 0 && sid < MAX_SCREENS); // sid within range
  // don't override already defined screens
  SDL_assert(!screens[sid].init && !screens[sid].quit &&
      !screens[sid].draw && !screens[sid].update);

  screens[sid] = screen;
}

void *Game::get_globals() {
  return SDL_GetWindowData(window, "globals");
}

void Game::set_globals(void *globals) {
  SDL_SetWindowData(window, "globals", globals);
}

Game Game::instance;

