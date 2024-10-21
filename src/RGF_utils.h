#pragma once

#include <SDL.h>

namespace RGF {

  void draw_text(int font_id, float x, float y, const char *fmt, ...);
  // the dst rectangle SDL uses here is { x, y, src.w, src.h }
  void draw_clip(int tex_id, int x, int y, const SDL_Rect &src);

}
