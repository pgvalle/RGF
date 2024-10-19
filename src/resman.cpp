#include "resman.h"
#include "app.h"

void ResMan::free_everything() {
  for (auto& [_, texture] : textures)
    SDL_DestroyTexture(texture);
  textures.clear();

  for (auto& [_, font] : fonts)
    FC_FreeFont(font);
  fonts.clear();
}

SDL_Texture *ResMan::load_texture(int id, const char *path) {
  SDL_assert(textures.find(id) == textures.end()); // texture must not exist yet

  textures[id] = IMG_LoadTexture(App::instance.renderer, path);
  return textures[id];
}

SDL_Texture *ResMan::get_texture(int id) {
  if (textures.find(id) == textures.end())
    return NULL;
  return textures.at(id);
}

void ResMan::free_texture(int id) {
  if (textures.find(id) == textures.end())
    return;

  SDL_DestroyTexture(textures.at(id));
  textures.erase(id);
}

FC_Font *ResMan::load_font(int id, const char *path) {
  return NULL;
}

FC_Font *ResMan::get_font(int id) {
  if (fonts.find(id) == fonts.end())
    return NULL;
  return fonts.at(id);
}

void ResMan::free_font(int id) {
  if (fonts.find(id) == fonts.end())
    return;

  FC_FreeFont(fonts.at(id));
  fonts.erase(id);
}

ResMan ResMan::instance;
