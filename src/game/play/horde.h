#pragma once

#include <vector>

struct Horde {
  struct Invader {
    int type;
    int x, y;

    Invader(int row, int col);

    void draw() const;
    void move(int dx, int dy);
  };

  std::vector<Invader> invaders;
  int i;
  int dx, dy;

  Horde();

  void draw() const;
  void move();
  void populate();
};
