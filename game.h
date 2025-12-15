#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "textureManager.h"

void setDesiredFPS(int fps);
int getDesiredFPS();
double getDesiredMaxMilPerFrame();
void setDeltaTime(double delta);
double getDeltaTime();

void setRunning(int newRunning);
int isRunning();

SDL_Renderer * getRenderer();
SDL_Window * get_window();

void initGame(const char * windowLabel, int winWidth, int winHeight);

void handleInput();
void update();
void render();

void clearGame();


#endif //SPACE_INVADERS_GAME_H