#pragma once

#include <RGF_App.h>
#include <RGF_ResMan.h>

// Shared stuff

extern struct SICGlobals {
  int credits, score, hi_score;
} sic;

// DEFINING SCREENS

#define SPLASH_SCREEN 0

void splash_init();
void splash_quit();
void splash_draw();
int splash_update(const RGF::EventList &events, float dt);

// ASSETS

#define FONT_ASSET 0
#define CANNON_ASSET 0
#define INVADER1_ASSET 1
#define INVADER2_ASSET 2
#define INVADER3_ASSET 3
#define INVADER_DEATH_ASSET 4
#define UFO_ASSET 5

// OTHER STUFF

#define WIDTH  224
#define HEIGHT 256
