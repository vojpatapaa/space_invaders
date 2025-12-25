#ifndef SPACE_INVADERS_BUBAK_H
#define SPACE_INVADERS_BUBAK_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "textureManager.h"

typedef enum
{
    BUBAK_TYPE_GENERAL = 0,
    BUBAK_TYPE_COMMANDER,
    BUBAK_TYPE_SOLIDER,
    BUBAK_TYPE_EXPLODED,
    BUBAK_TYPE_DEAD
}BubakType;

typedef struct
{
    BubakType type;
    double xPos;
    double yPos;
    int width;
    int height;
    int alive;
    int spritePos;
}Bubak;

void initBubakModule();
void quitBubakModule();

double getBubakTopPos(Bubak * bubak);
double getBubakRightPos(Bubak * bubak);
double getBubakBottomPos(Bubak * bubak);
double getBubakLeftPos(Bubak * bubak);

Bubak createBubak(double x, double y, int bubakWidth, int bubakHeight, BubakType bubakType);
void moveSpritePositionRight(Bubak * bubak);
void updateBubak(Bubak * bubak);
void renderBubak(Bubak * bubak);


#endif