#ifndef SPACE_INVADERS_PROJECTILE_H
#define SPACE_INVADERS_PROJECTILE_H

#include <SDL2/SDL.h>
#include "dynamic_array.h"

typedef enum
{
    PROJECTILE_TYPE_ENEMY = 0,
    PROJECTILE_TYPE_TANK
}ProjectileType;

typedef struct 
{
    double xPos;
    double yPos;
    int width;
    int height;
    ProjectileType type;
    double speed;
}Projectile;

void initProjectileModule();
void quitProjectileModule();
dynarray * getShots();

Projectile * createProjectile(double x, double y, int width, int height, ProjectileType projectileType, double speed);

void updateProjectile(Projectile * projectile);
void renderProjectile(Projectile * projectile);
void destroyProjectile(Projectile * projectile);

void updateProjectiles();
void renderProjectiles();


#endif