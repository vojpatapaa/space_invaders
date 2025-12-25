#ifndef SPACE_INVADERS_SHILED_H
#define SPACE_INVADERS_SHILED_H

#include <SDL2/SDL.h>

#define CUBE_WIDTH 18
#define CUBE_HEIGHT 18
#define BLOCK_COUNT 5
#define BLOCK_LIFES 3

typedef struct
{
    double xPos;
    double yPos;
    int width;
    int height;
    int lifes;
}ShieldBlock;


typedef struct
{
    double xPos;
    double yPos;
    SDL_Color color;

    ShieldBlock leftStand;
    ShieldBlock leftCube;
    ShieldBlock bridge;
    ShieldBlock rightCube;
    ShieldBlock rightStand;
}Shield;

Shield createShield(double x, double y, SDL_Color backgroundColor);
void updateShield(Shield * shield);
void renderShield(Shield * shield);


#endif