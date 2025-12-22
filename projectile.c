#include "projectile.h"
#include "game.h"
#include <stdlib.h>

Projectile * createProjectile(double x, double y, int width, int height, ProjectileType projectileType, double speed)
{
    Projectile * projectile = (Projectile *)malloc(sizeof(Projectile));
    if(projectile == NULL)
    {
        return NULL;
    }

    projectile->xPos = x;
    projectile->yPos = y;
    projectile->width = width;
    projectile->height = height;
    projectile->type = projectileType;
    projectile->speed = speed;

    return projectile;
}

void updateProjectile(Projectile * projectile)
{
    projectile->yPos += projectile->speed * getDeltaTime();
}

void renderProjectile(Projectile * projectile)
{
    SDL_Rect dst;
    dst.x = (int)projectile->xPos;
    dst.y = (int)projectile->yPos;
    dst.w = projectile->width;
    dst.h = projectile->height;

    switch (projectile->type)
    {
        case PROJECTILE_TYPE_ENEMY:
            SDL_SetRenderDrawColor(getRenderer(), 255, 165, 0, 255);
            break;

        case PROJECTILE_TYPE_TANK:
            SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 255);
            break;
            
        
        default:
            break;
    }

    SDL_RenderFillRect(getRenderer(), &dst);
}

void destroyProjectile(Projectile * projectile)
{
    if(projectile != NULL)
    {
        free(projectile);
    }
}