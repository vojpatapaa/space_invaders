#ifndef SPACE_INVADERS_TANK_H
#define SPACE_INVADERS_TANK_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "textureManager.h"

#define TANK_PROJECTILE_SPEED 300
#define TANK_PROJECTILE_WIDTH 4
#define TANK_PROJECTILE_HEIGHT 9

typedef struct 
{
    double xPos;
    double yPos;
    int width;
    int height;
    int lives;

    Uint64 lastShootTime;
    int DelayTime;

    int activeInput;
}Tank;

void initTankModule();
void quitTankModule();

Tank createTank(double x, double y, int tankWidth, int tankHeight, int miliShootDelay);

void updateTank(Tank * tank);
void renderTank(Tank * tank);




#endif