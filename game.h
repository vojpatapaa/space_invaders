#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

typedef struct
{
    int x;
    int y;
    int leftClicked;
}MouseState;

typedef enum
{
    GAME_PART_MENU = 0,
    GAME_PART_PLAY
}GamePart;

void setDesiredFPS(int fps);
int getDesiredFPS();
double getDesiredMaxMilPerFrame();
void setDeltaTime(double delta);
double getDeltaTime();
GamePart getCurrentGamePart();
void setCurrentGamePart(GamePart gamePart);

void setRunning(int newRunning);
int isRunning();

int getWindowWidth();
int getWindowHeight();
int getCanvasWidth();
int getCanvasHeight();
void setBackgroundColor(SDL_Color backgroundColor);
SDL_Color getBackgroundColor();

MouseState * getMouseState();

SDL_Renderer * getRenderer();
SDL_Window * get_window();

void initGameSessionWithoutTank();
void initMenuSession();

void initGame(const char * windowLabel, int winWidth, int winHeight, int initialFPS, SDL_Color backgroundColor);

void handleInput();
void update();
void render();

void clearGame();


#endif