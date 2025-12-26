#include "ufo.h"
#include "textureManager.h"
#include "game.h"
#include "projectile.h"

SDL_Texture * ufoTexture;
const char * UFO_TEXTURE_PATH= "assets/ufo/textures/ufo.png";

void initUfoModule()
{
    ufoTexture = createTextureFromImage(UFO_TEXTURE_PATH);
}

void quitUfoModule()
{
    SDL_DestroyTexture(ufoTexture);
}

Ufo createUfo(double x, double y, int width, int height, int delay, int speed)
{
    Ufo ufo;

    ufo.xPos = x;
    ufo.yPos = y;
    ufo.width = width;
    ufo.height = height;
    ufo.delay = delay;
    ufo.speed = speed;
    ufo.lastFlyTime = 0;
    ufo.fly = 0;
    ufo.direction = UFO_DIRECTION_RIGHT;

    return ufo;
}


void updateUfo(Ufo * ufo)
{
    SDL_Rect ufoDst;
    dynarray * shots = getShots();
    Uint64 currentTime = SDL_GetPerformanceCounter();
    int elapsedTime = (currentTime - ufo->lastFlyTime) / (double)SDL_GetPerformanceFrequency() * 1000;

    if(elapsedTime >= ufo->delay)
    {
        ufo->fly = 1;
    }

    if(ufo->fly)
    {
        switch (ufo->direction)
        {
            case UFO_DIRECTION_RIGHT:
                ufo->xPos += ufo->speed * getDeltaTime();
                if(ufo->xPos >= getCanvasWidth())
                {
                    ufo->fly = 0;
                    ufo->direction = UFO_DIRECTION_LEFT;
                    ufo->lastFlyTime = SDL_GetPerformanceCounter();
                }
                break;

            case UFO_DIRECTION_LEFT:
                ufo->xPos -= ufo->speed * getDeltaTime();
                if(ufo->xPos + ufo->width <= 0)
                {
                    ufo->fly = 0;
                    ufo->direction = UFO_DIRECTION_RIGHT;
                    ufo->lastFlyTime = SDL_GetPerformanceCounter();
                }
                break;
            
            default:
                break;
        }
    }

    //check collision
    ufoDst.x = (int)ufo->xPos;
    ufoDst.y = (int)ufo->yPos;
    ufoDst.w = ufo->width;
    ufoDst.h = ufo->height;


    for (int i = shots->size - 1; i >=0; i--)
    {
        Projectile * shot = shots->items[i];
        SDL_Rect shotDst;

        shotDst.x = (int)shot->xPos;
        shotDst.y = (int)shot->yPos;
        shotDst.w = shot->width;
        shotDst.h = shot->height;

        if(shot->type == PROJECTILE_TYPE_TANK && SDL_HasIntersection(&shotDst, &ufoDst))
        {
            destroyProjectile(shot);
        }

    }
    
}


void renderUfo(Ufo * ufo)
{
    SDL_Rect dst;


    dst.x = (int)ufo->xPos;
    dst.y = (int)ufo->yPos;
    dst.w = ufo->width;
    dst.h = ufo->height;

    SDL_RenderCopy(getRenderer(), ufoTexture, NULL, &dst);
}