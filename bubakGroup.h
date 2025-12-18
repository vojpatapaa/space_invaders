#ifndef SPACE_INVADERS_BUBAK_GROUP_H
#define SPACE_INVADERS_BUBAK_GROUP_H

#define BUBAK_COLUMNS 11
#define BUBAK_GENERAL_ROWS 1
#define BUBAK_COMMANDER_ROWS 2
#define BUBAK_SOLIDER_ROWS 2
/*!!!MUSI BYT SOUCET 3 PREDCHOZICH MAKER!!!*/
#define BUBAK_ROWS 5


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "bubak.h"


typedef struct
{
    Bubak bubaks[BUBAK_ROWS][BUBAK_COLUMNS];
    int minDelay;
    int maxDelay;
    int currentDelay;
    double padding;
    double bubakWidth;
    double bubakHeight;
}BubakGroup;

BubakGroup createBubakGroup(int minDelayMs, int maxDelayMs, int paddingg, double bubakWidthh, double bubakHeightt);
void updateBubakGroup(BubakGroup * bubakGroup);
void renderBubakGroup(BubakGroup * bubakGroup);

#endif