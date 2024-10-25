#include "ufo.h"
#include "../SIC.h"

#define UFO_Y 40
#define UFO_LL 8   // left limit
#define UFO_RL 192 // right limit

#define UFO_VX 25

#define UFO_TSS 2 // Time Showing Score
#define UFO_TOE 2 // Time Of Explosion
#define UFO_TTR 10 // Time To Respawn

using namespace RGF;

// Explosion *UFO::collisionCallback()
// {
//   state = UFO_EXPLODING;
//   ticker.reset(UFO_TICKS_EXPLODING);

//   Explosion *e = new Explosion;
//   e->x = x - 4; // offset bc explosion sprite width is 8 pixels bigger
//   e->y = UFO_Y;
//   e->clip = {16, 0, 24, 8};
//   e->lifespan.reset(UFO_TICKS_EXPLODING);
//   return e;
// }

// SDL_Rect UFO::getCollider() const
// {
//   return {(int)round(x), UFO_Y, 16, 8};
// }

void UFO::draw() const {
  SDL_SetRenderDrawColor(App::instance.renderer, 255, 0, 0, 255); // red

  switch (state) {
    case ALIVE:
      draw_clip(UFO_ASSET, x, UFO_Y, {0, 0, 24, 8});
      break;
    case EXPLODING:
      draw_clip(UFO_ASSET, x, UFO_Y, {24, 0, 24, 8});
      break;
    case SHOWING_SCORE:
      draw_text(FONT_ASSET, x, UFO_Y, "%d", score);
      break;
  }
}

void UFO::update(float dt) {
  switch (state) {
    case AWAY:
      time += dt;
      if (time < UFO_TTR)
        break;
      state = ALIVE;
      x = (rand() % 2 ? UFO_LL : UFO_RL); // choose a corner
      vx = (x == UFO_LL ? UFO_VX : -UFO_VX); // set correct velocity
      time = 0;
      break;
    case ALIVE:
      x += dt * vx;
      if (UFO_LL <= x && x <= UFO_RL)
        break;
      state = AWAY;
      time = 0;
      break;
    case EXPLODING:
      time += dt;
      if (time < UFO_TOE)
        break;
      state = SHOWING_SCORE;
      time = 0;
      //sic->score += 100; // TODO: generate random score
      break;
    case SHOWING_SCORE:
      time += dt;
      if (time < UFO_TSS)
        break;
      state = AWAY;
      time = 0;
      break;
  }
}

