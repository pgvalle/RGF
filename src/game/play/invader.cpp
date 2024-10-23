#include "invader.h"
#include "../SIC.h"

using namespace RGF;

Invader::Invader(int row, int col) {
  type = INVADER1_ASSET;
  if (row > 2)
    type = INVADER3_ASSET;
  else if (row > 0)
    type = INVADER2_ASSET;

  x = 2 + 8 * (3 + 2 * col);
  y = 0 + 8 * (8 + 2 * row);
}

//Explosion *Invader::onHit()
//{
//  const int scoreValue =  10 * (3 - type);
//  g->add2Score(scoreValue);
//
//  Explosion *e = new Explosion;
//  e->x = x;
//  e->y = y;
//  e->clip = {28, 16, 13, 8};
//  e->lifespan.reset(0.5);
//  return e;
//}

//SDL_Rect Invader::getHitbox() const
//{
//  if (type == 2)
//    return {x - 2, y, 12, 8};
//  else if (type == 1)
//    return {x - 1, y, 11, 8};
//  return {x, y, 8, 8};
//}

void Invader::draw() const {
  int frame = (x % 4) > 1;

  switch (type) {
    case INVADER1_ASSET:
      draw_clip(type, x + 2, y, { frame * 8, 0, 8, 8 });
      break;
    case INVADER2_ASSET:
      draw_clip(type, x + 1, y, { frame * 11, 0, 11, 8 });
      break;
    case INVADER3_ASSET:
      draw_clip(type, x, y, { frame * 12, 0, 12, 8 });
      break;
  }
}

void Invader::move(int dx, int dy) {
  x += dx;
  y += dy;
}
