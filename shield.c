#include "shield.h"
#include "projectile.h"
#include "game.h"

Shield createShield(double x, double y, SDL_Color backgroundColor)
{
    Shield shield;

    shield.color = backgroundColor;
    shield.xPos = x;
    shield.yPos = y;

    shield.leftCube.xPos = x;
    shield.leftCube.yPos = y;
    shield.leftCube.width = CUBE_WIDTH;
    shield.leftCube.height = CUBE_HEIGHT;
    shield.leftCube.lifes = BLOCK_LIFES;

    shield.leftStand.xPos = x;
    shield.leftStand.yPos = y + CUBE_WIDTH;
    shield.leftStand.width = CUBE_WIDTH;
    shield.leftStand.height = CUBE_HEIGHT * 2;
    shield.leftStand.lifes = BLOCK_LIFES;

    shield.bridge.xPos = x + CUBE_WIDTH;
    shield.bridge.yPos = y;
    shield.bridge.width = CUBE_WIDTH * 2;
    shield.bridge.height = CUBE_HEIGHT;
    shield.bridge.lifes = BLOCK_LIFES;

    shield.rightCube.xPos = x + CUBE_WIDTH + 2 * CUBE_WIDTH;
    shield.rightCube.yPos = y;
    shield.rightCube.width = CUBE_WIDTH;
    shield.rightCube.height = CUBE_HEIGHT;
    shield.rightCube.lifes = BLOCK_LIFES;

    shield.rightStand.xPos = x + CUBE_WIDTH + 2 * CUBE_WIDTH;;
    shield.rightStand.yPos = y + CUBE_WIDTH;
    shield.rightStand.width = CUBE_WIDTH;
    shield.rightStand.height = CUBE_HEIGHT * 2;
    shield.rightStand.lifes = BLOCK_LIFES;

    return shield;
}


void updateShield(Shield * shield)
{
    SDL_Rect blockDst;
    SDL_Rect shotDst;
    dynarray * shots = getShots();
    ShieldBlock * arr[BLOCK_COUNT];
    arr[0] = &shield->leftStand;
    arr[1] = &shield->leftCube;
    arr[2] = &shield->bridge;
    arr[3] = &shield->rightCube;
    arr[4] = &shield->rightStand;

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
        blockDst.x = (int)arr[i]->xPos;
        blockDst.y = (int)arr[i]->yPos;
        blockDst.w = arr[i]->width;
        blockDst.h = arr[i]->height;

        for (int j = shots->size-1; j >= 0; j--)
        {
            Projectile * shot = shots->items[j];
            shotDst.x = (int)shot->xPos;
            shotDst.y = (int)shot->yPos;
            shotDst.w = shot->width;
            shotDst.h = shot->height;


            if(SDL_HasIntersection(&shotDst, &blockDst) && arr[i]->lifes > 0)
            {
                destroyProjectile(shot);
                arr[i]->lifes--;
            }
        }
        
    }
    
}


void renderShield(Shield * shield)
{
    ShieldBlock * arr[BLOCK_COUNT];
    SDL_Rect blockDst;
    arr[0] = &shield->leftStand;
    arr[1] = &shield->leftCube;
    arr[2] = &shield->bridge;
    arr[3] = &shield->rightCube;
    arr[4] = &shield->rightStand;

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
        blockDst.x = (int)arr[i]->xPos;
        blockDst.y = (int)arr[i]->yPos;
        blockDst.w = arr[i]->width;
        blockDst.h = arr[i]->height;

        switch (arr[i]->lifes)
        {
            case 3:
                SDL_SetRenderDrawColor(getRenderer(), shield->color.r, shield->color.g, shield->color.b, 255);
                SDL_RenderFillRect(getRenderer(), &blockDst);
                break;
            
            case 2:
                SDL_SetRenderDrawColor(getRenderer(), shield->color.r, shield->color.g, shield->color.b, 170);
                SDL_RenderFillRect(getRenderer(), &blockDst);
                break;

            case 1:
                SDL_SetRenderDrawColor(getRenderer(), shield->color.r, shield->color.g, shield->color.b, 85);
                SDL_RenderFillRect(getRenderer(), &blockDst);
                break;
            
            default:
                break;
        }
    }
    
}