#include "RGF_utils.h"
#include "RGF_App.h"
#include "RGF_ResMan.h"
#include <cstdio>
#include <cstdarg>

void RGF::draw_text(int font_id, float x, float y, const char *fmt, ...) {
  static char buffer[1024];
  va_list args;

  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  FC_Draw(
      ResMan::instance.get_font(font_id),
      App::instance.renderer,
      x,
      y,
      buffer);
}

void RGF::draw_clip(int tex_id, int x, int y, const SDL_Rect &src) {
  SDL_Rect dst = { x, y, src.w, src.h };

  SDL_RenderCopy(
      App::instance.renderer,
      ResMan::instance.get_texture(tex_id),
      &src,
      &dst);
}

