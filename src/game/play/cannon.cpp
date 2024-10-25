#include "cannon.h"
#include "../SIC.h"

using namespace RGF;

void Cannon::draw() const {
  switch (state) {
    case ALIVE:
      draw_clip(CANNON_ASSET, x, Y, { 0, 0, 16, 8 });
      break;
    case DYING:
      draw_clip(CANNON_ASSET, x, Y, { 16 + 16 * death_frame, 0, 16, 8 });
      break;
  }
}

void Cannon::update(float dt) {
  switch (state) {
    case ALIVE:
      time1 += dt; // to shoot
      x += dt * vx;
      break;
    case DYING:
      // frame change
      time1 += dt;
      if (time1 >= 0.1) {
        time1 = 0;
        death_frame = !death_frame;
      }
      // dying state over
      time2 += dt;
      if (time2 >= 2) {
        state = DEAD;
        time1 = 0; // time1 for death time
        time2 = 0;
        death_frame = 0;
      }
      break;
    case DEAD:
      time1 += dt;
      if (time1 >= 1) {
        state = ALIVE;
        time1 = 0; // time1 for death time
        x = 16;
        vx = 0;
      }
      break;
  }
}
