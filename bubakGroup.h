#ifndef SPACE_INVADERS_BUBAK_GROUP_H
#define SPACE_INVADERS_BUBAK_GROUP_H

#define BUBAK_COLUMNS 11
#define BUBAK_GENERAL_ROWS 1
#define BUBAK_COMMANDER_ROWS 2
#define BUBAK_SOLIDER_ROWS 2
/*!!!MUSI BYT SOUCET 3 PREDCHOZICH MAKER!!!*/
#define BUBAK_ROWS 5

#define BUBAK_HORIZONTAL_SPEED 15
#define BUBAK_VERTICAL_SPEED 30

#define BUBAK_PROJECTILE_SPEED 500
#define BUBAK_PROJECTILE_WIDTH 4 
#define BUBAK_PROJECTILE_HEIGHT 18


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "bubak.h"

typedef enum
{
    RIGHT = 0,
    DOWN,
    LEFT,
    UP
}Direction;


typedef struct
{
    Bubak bubaks[BUBAK_ROWS][BUBAK_COLUMNS];
    int minDelay;
    int maxDelay;
    int currentDelay;
    int padding;
    int bubakWidth;
    int bubakHeight;
    Uint64 lastUpdateTime;
    Direction direction;
}BubakGroup;

int getAliveBubaks(BubakGroup * bubakGroup);
Bubak * getLeadingRightBubak(BubakGroup * bubakGroup);
Bubak * getLeadingLeftBubak(BubakGroup * bubakGroup);

BubakGroup createBubakGroup(int minDelayMs, int maxDelayMs, int paddingg, int bubakWidthh, int bubakHeightt);
void updateBubakGroup(BubakGroup * bubakGroup);
void renderBubakGroup(BubakGroup * bubakGroup);

#endif