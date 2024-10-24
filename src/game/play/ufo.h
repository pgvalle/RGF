#pragma once

struct UFO {
  enum UFOState {
    UFO_AWAY,
    UFO_ALIVE,
    UFO_EXPLODING,
    UFO_SHOWING_SCORE,
    UFO_DEAD
  };

  UFOState state = UFO_AWAY;
  float x = 1e10, vx = 0;
  int score = 0;
  float time = 0;
  
  void draw() const;
  void update(float dt);
};
