#pragma once

struct Cannon {
  enum CannonState {
    ALIVE,
    DYING,
    DEAD
  };

  static const int Y = 216;

  CannonState state = DEAD;
  float time1 = 0, time2 = 0;
  float x = 16, vx = 0;
  int death_frame = 0;

  void draw() const;
  void update(float dt);
};
