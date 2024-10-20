#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>

int RGF_main(int argc, char **argv);

int main(int argc, char **argv) {
  int ret;

  srand(time(NULL));

  // make sure all libraries are initialized
  SDL_assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);
  SDL_assert(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG);
  SDL_assert(TTF_Init() == 0);

  ret = RGF_main(argc, argv);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return ret;
}
