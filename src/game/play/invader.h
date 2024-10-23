#pragma once

#include "../SIC.h"

struct Invader
{
  int type;
  int x, y;

  Invader(int row, int col);

  void draw() const;
  void move(int dx, int dy);
};
