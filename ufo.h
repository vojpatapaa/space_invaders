#ifndef SPACE_INVADERS_UFO_H
#define SPACE_INVADERS_UFO_H

#include <SDL2/SDL.h>

typedef enum
{
    UFO_DIRECTION_RIGHT = 0,
    UFO_DIRECTION_LEFT
}UfoDirection;

typedef struct
{
    double speed;
    double xPos;
    double yPos;
    int width;
    int height;
    int delay;
    Uint64 lastFlyTime;
    int fly;
    UfoDirection direction;
    
}Ufo;

void initUfoModule();
void quitUfoModule();

Ufo createUfo(double x, double y, int width, int height, int delay, int speed);
void updateUfo(Ufo * ufo);
void renderUfo(Ufo * ufo);


#endif