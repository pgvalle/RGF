#pragma once

struct UFO {
  enum UFOState {
    AWAY,
    ALIVE,
    EXPLODING,
    SHOWING_SCORE,
    DEAD
  };

  UFOState state = AWAY;
  float x = 1e10, vx = 0;
  int score = 0;
  float time = 0;
  
  void draw() const;
  void update(float dt);
};
