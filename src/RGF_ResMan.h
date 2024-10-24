#pragma once

#include <SDL.h>
#include <SDL_FontCache.h>
#include <unordered_map>

namespace RGF {

  class ResMan {
    private:
      std::unordered_map<int, SDL_Texture *> textures;
      std::unordered_map<int, FC_Font *> fonts;

      ResMan() {} // you can't instantiate a ResMan object.

    public:
      static ResMan instance; // Global instance of ResMan

      // Doesn't need to be called when quitting the game. Called automatically.
      void free_resources();

      SDL_Texture *load_texture(int id, const char *path);
      SDL_Texture *get_texture(int id);
      void free_texture(int id);

      FC_Font *load_font(int id, Uint32 pt, int style, const char *path);
      FC_Font *get_font(int id);
      void free_font(int id);
  };

}

