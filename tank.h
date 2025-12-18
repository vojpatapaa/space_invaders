#ifndef SPACE_INVADERS_TANK_H
#define SPACE_INVADERS_TANK_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "textureManager.h"

typedef struct 
{
    double xPos;
    double yPos;
    double width;
    double height;

    Uint64 lastShootTime;
    int DelayTime;

    int activeInput;
}Tank;

void initTankModule();
void quitTankModule();

Tank createTank(double x, double y, double tankWidth, double tankHeight, int miliShootDelay);

void updateTank(Tank * tank);
void renderTank(Tank * tank);




#endif