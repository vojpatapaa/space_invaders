#include "bubak.h"
#include "projectile.h"
#include "scoreManager.h"

SpriteSheet * soliderSpriteSheet;
const char * SOLIDER_BUBAK_TEXTURE_PATH = "assets/bubak/textures/bubak3.png";

SpriteSheet * commanderSpriteSheet;
const char * COMMANDER_BUBAK_TEXTURE_PATH = "assets/bubak/textures/bubak2.png";

SpriteSheet * generalSpriteSheet;
const char * GENERAL_BUBAK_TEXTURE_PATH = "assets/bubak/textures/bubak1.png";

SDL_Texture * explodedTexture;
const char * EXPLODED_BUBAK_TEXTURE_PATH = "assets/bubak/textures/explosion.png";

void initBubakModule()
{
    soliderSpriteSheet = createSpriteSheet(SOLIDER_BUBAK_TEXTURE_PATH, 12, 8, 2);
    commanderSpriteSheet = createSpriteSheet(COMMANDER_BUBAK_TEXTURE_PATH, 11, 8, 2);
    generalSpriteSheet = createSpriteSheet(GENERAL_BUBAK_TEXTURE_PATH, 8, 8, 2);
    explodedTexture = createTextureFromImage(EXPLODED_BUBAK_TEXTURE_PATH);
}


void quitBubakModule()
{
    destroySpriteSheet(soliderSpriteSheet);
    destroySpriteSheet(commanderSpriteSheet);
    destroySpriteSheet(generalSpriteSheet);
}

double getBubakTopPos(Bubak * bubak)
{
    return bubak->yPos;
}

double getBubakRightPos(Bubak * bubak)
{
    return bubak->xPos + bubak->width;
}

double getBubakBottomPos(Bubak * bubak)
{
    return bubak->yPos + bubak->height;
}

double getBubakLeftPos(Bubak * bubak)
{
    return bubak->xPos;
}

Bubak createBubak(double x, double y, int bubakWidth, int bubakHeight, BubakType bubakType)
{
    Bubak bubak;

    bubak.alive = 1;
    bubak.spritePos = 0;
    bubak.xPos = x;
    bubak.yPos = y;
    bubak.width = bubakWidth;
    bubak.height = bubakHeight;
    bubak.type = bubakType;

    return bubak;
}

void moveSpritePositionRight(Bubak * bubak)
{
    switch (bubak->type)
    {
        case BUBAK_TYPE_SOLIDER:
            bubak->spritePos = (bubak->spritePos + 1) % soliderSpriteSheet->boxCount;
            break;

        case BUBAK_TYPE_COMMANDER:
            bubak->spritePos = (bubak->spritePos + 1) % commanderSpriteSheet->boxCount;
            break;

        case BUBAK_TYPE_GENERAL:
            bubak->spritePos = (bubak->spritePos + 1) % generalSpriteSheet->boxCount;
            break;

        default:
            break;
    }
}


void updateBubak(Bubak * bubak)
{
    //kolize s nepratelkskymi strelami
    dynarray * shots = getShots();
    SDL_Rect bubakDst;
    SDL_Rect shotDst;

    bubakDst.x = (int)bubak->xPos;
    bubakDst.y = (int)bubak->yPos;
    bubakDst.w = bubak->width;
    bubakDst.h = bubak->height;

    for (int k = shots->size - 1; k >= 0; k--)
    {
        Projectile * shot = shots->items[k];

        shotDst.x = (int)shot->xPos;
        shotDst.y = (int)shot->yPos;
        shotDst.w = shot->width;
        shotDst.h = shot->height;

        if(bubak->alive && shot->type == PROJECTILE_TYPE_TANK && SDL_HasIntersection(&shotDst, &bubakDst))
        {
            switch (bubak->type)
            {
                case BUBAK_TYPE_SOLIDER:
                    addToScore(5);
                    break;

                case BUBAK_TYPE_COMMANDER:
                    addToScore(10);
                    break;

                case BUBAK_TYPE_GENERAL:
                    addToScore(20);
                    break;
                
                default:
                    break;
            }

            bubak->alive = 0;
            bubak->type = BUBAK_TYPE_EXPLODED;
            destroyProjectile(shot);
        }   
    }
}

void renderBubak(Bubak * bubak)
{
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Rect src = {0, 0, 0, 0};

    dst.x = (int)bubak->xPos;
    dst.y = (int)bubak->yPos;
    dst.w = bubak->width;
    dst.h = bubak->height;

    switch (bubak->type)
    {
        case BUBAK_TYPE_SOLIDER:
            src.w = soliderSpriteSheet->boxWidth;
            src.h = soliderSpriteSheet->boxHeight;
            src.x = bubak->spritePos * soliderSpriteSheet->boxWidth;
            src.y = 0;

            SDL_RenderCopy(getRenderer(), soliderSpriteSheet->texture, &src, &dst);
            break;

        case BUBAK_TYPE_COMMANDER:
            src.w = commanderSpriteSheet->boxWidth;
            src.h = commanderSpriteSheet->boxHeight;
            src.x = bubak->spritePos * commanderSpriteSheet->boxWidth;
            src.y = 0;

            SDL_RenderCopy(getRenderer(), commanderSpriteSheet->texture, &src, &dst);
            break;

        case BUBAK_TYPE_GENERAL:
            src.w = generalSpriteSheet->boxWidth;
            src.h = generalSpriteSheet->boxHeight;
            src.x = bubak->spritePos * generalSpriteSheet->boxWidth;
            src.y = 0;

            SDL_RenderCopy(getRenderer(), generalSpriteSheet->texture, &src, &dst);
            break;

        case BUBAK_TYPE_EXPLODED:
            SDL_RenderCopy(getRenderer(), explodedTexture, NULL, &dst);
            break;

        default:
            break;
    }
}

void destroyBubak(Bubak * bubak)
{
    free(bubak);
}