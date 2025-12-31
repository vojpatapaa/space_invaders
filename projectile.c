#include "projectile.h"
#include "game.h"

dynarray shots;



void initProjectileModule()
{
    dynarray_init(&shots, 10);
}


void quitProjectileModule()
{
    dynarray_free(&shots);
}

dynarray * getShots()
{
    return &shots;
}

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

    dynarray_push(&shots, projectile);

    return projectile;
}

void updateProjectile(Projectile * projectile)
{
    switch (projectile->type)
    {
        case PROJECTILE_TYPE_ENEMY:
            projectile->yPos += projectile->speed * getDeltaTime();
            break;

        case PROJECTILE_TYPE_TANK:
            projectile->yPos -= projectile->speed * getDeltaTime();
            break;

        default:
            break;
        }

    if(projectile->yPos > getCanvasHeight() || projectile->yPos + projectile->height < 0 )
    {
        dynarray_remove(&shots, projectile);
    }
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
    dynarray_remove(&shots, projectile);
}


void updateProjectiles()
{
    int i = 0;
    while (i < shots.size)
    {
        Projectile * projectile = shots.items[i];
        updateProjectile(projectile);

        if (i < shots.size && shots.items[i] == projectile)
        {
            i++;
        }
    }
}

void renderProjectiles()
{
    int count = shots.size;
    for (int i = 0; i < count; i++)
    {
        renderProjectile(shots.items[i]);
    }
}