#pragma once

#include <RGF.h>

// Shared stuff

extern struct SICGlobals {
  int credits, score, hi_score;
} sic;

// DEFINING SCREENS

#define SPLASH_SCREEN 1

void splash_init(int prev_screen);
void splash_quit();
void splash_draw();
int splash_update(float dt);
void splash_handle_event(const SDL_Event &event);

#define PLAY_SCREEN 0

void play_init(int prev_screen);
void play_quit();
void play_draw();
int play_update(float dt);
void play_handle_event(const SDL_Event &event);

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
