#pragma once

enum UFOState {
  UFO_AWAY,
  UFO_ALIVE,
  UFO_EXPLODING,
  UFO_SHOWING_SCORE,
  UFO_DEAD
};

struct UFO {
  UFOState state = UFO_AWAY;
  float x, vx;
  int score;
  float time = 0;
  
  void draw() const;
  void update(float dt);
};
