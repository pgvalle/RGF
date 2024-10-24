#pragma once

#include <RGF.h>

// Assets

#define FONT_ASSET 0
#define CANNON_ASSET 0
#define INVADER1_ASSET 1
#define INVADER2_ASSET 2
#define INVADER3_ASSET 3
#define INVADER_DEATH_ASSET 4
#define UFO_ASSET 5

// Other settings

#define WIDTH  224
#define HEIGHT 256

// Global data

extern struct Globals {
  int credits, score, hi_score;
} g;

// All screens

#define SPLASH_SCREEN 0

void splash_init();
void splash_quit();
void splash_draw();
int splash_update(float dt);
void splash_handle_event(const SDL_Event &event);

#define PLAY_SCREEN 1

void play_init();
void play_quit();
void play_draw();
int play_update(float dt);
void play_handle_event(const SDL_Event &event);

#define PAUSE_SCREEN 2

void pause_init();
void pause_quit();
void pause_draw();
int pause_update(float dt);
void pause_handle_event(const SDL_Event &event);
