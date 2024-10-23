#pragma once

struct Horde {
  std::vector<Invader> invaders;
  int i;
  int dx, dy;

  void draw() const;
  void update();
};
