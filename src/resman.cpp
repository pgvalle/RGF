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

  if (textures[id] == NULL) {
    textures.erase(id);
    return NULL;
  }

  return textures[id];
}

SDL_Texture *ResMan::get_texture(int id) {
  if (textures.find(id) == textures.end())
    return NULL;
  return textures[id];
}

void ResMan::free_texture(int id) {
  if (textures.find(id) == textures.end())
    return;

  SDL_DestroyTexture(textures[id]);
  textures.erase(id);
}

FC_Font *ResMan::load_font(int id, Uint32 pt, int style, const char *path) {
  SDL_assert(fonts.find(id) == fonts.end()); // font must not exist yet

  Uint8 success;

  fonts[id] = FC_CreateFont();
  success = FC_LoadFont(
      fonts[id],
      App::instance.renderer,
      path,
      pt,
      { 255, 255, 255, 255 },
      style);

  // if unsuccessful, unbind id to font and free the font
  if (!success) {
    FC_FreeFont(fonts[id]);
    fonts.erase(id);
    return NULL;
  }

  return fonts[id];
}

FC_Font *ResMan::get_font(int id) {
  if (fonts.find(id) == fonts.end())
    return NULL;
  return fonts[id];
}

void ResMan::free_font(int id) {
  if (fonts.find(id) == fonts.end())
    return;

  FC_FreeFont(fonts.at(id));
  fonts.erase(id);
}

ResMan ResMan::instance;
