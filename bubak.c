#include "bubak.h"

SpriteSheet * soliderSpriteSheet;
const char * SOLIDER_BUBAK_TEXTURE_PATH = "assets/bubak/textures/bubak3.png";

SpriteSheet * commanderSpriteSheet;
const char * COMMANDER_BUBAK_TEXTURE_PATH = "assets/bubak/textures/bubak2.png";

SpriteSheet * generalSpriteSheet;
const char * GENERAL_BUBAK_TEXTURE_PATH = "assets/bubak/textures/bubak1.png";

void initBubakModule()
{
    soliderSpriteSheet = createSpriteSheet(SOLIDER_BUBAK_TEXTURE_PATH, 12, 8, 2);
    commanderSpriteSheet = createSpriteSheet(COMMANDER_BUBAK_TEXTURE_PATH, 11, 8, 2);
    generalSpriteSheet = createSpriteSheet(GENERAL_BUBAK_TEXTURE_PATH, 8, 8, 2);
}


void quitBubakModule()
{
    destroySpriteSheet(soliderSpriteSheet);
    destroySpriteSheet(commanderSpriteSheet);
    destroySpriteSheet(generalSpriteSheet);
}

Bubak createBubak(double x, double y, double bubakWidth, double bubakHeight, BubakType bubakType)
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

}

void renderBubak(Bubak * bubak)
{
    SDL_Rect dst = {0, 0, 0, 0};
    SDL_Rect src = {0, 0, 0, 0};

    dst.x = (int)bubak->xPos;
    dst.y = (int)bubak->yPos;
    dst.w = (int)bubak->width;
    dst.h = (int)bubak->height;

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

        default:
            break;
    }
}

void destroyBubak(Bubak * bubak)
{
    free(bubak);
}