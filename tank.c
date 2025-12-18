#include "tank.h"

#define MOVE_SPEED 250.0

static SDL_Texture * tankTexture = NULL;
static const char * TANK_TEXTURE_PATH = "assets/tank/textures/tank.png";

void initTankModule()
{
    tankTexture = createTextureFromImage(TANK_TEXTURE_PATH);
}

void quitTankModule()
{
    SDL_DestroyTexture(tankTexture);
}

Tank createTank(double x, double y, double tankWidth, double tankHeight, int miliShootDelay)
{
    Tank tank;

    tank.DelayTime = miliShootDelay;
    tank.lastShootTime = 0;

    tank.xPos = x;
    tank.yPos = y;
    tank.width = tankWidth;
    tank.height = tankHeight;
    tank.activeInput = 1;


    return tank;
}

void updateTank(Tank * tank)
{
    if(tank->activeInput)
    {
        const Uint8 * keyboardState = SDL_GetKeyboardState(NULL);
        if(keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A])
        {
            tank->xPos -= getDeltaTime() * MOVE_SPEED;
        }

        if(keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D])
        {
            tank->xPos += getDeltaTime() * MOVE_SPEED;
        }

        if(keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_SPACE])
        {
            Uint64 currentTime = SDL_GetPerformanceCounter();
            if((currentTime - tank->lastShootTime)/(double)SDL_GetPerformanceFrequency() * 1000 >= tank->DelayTime)
            {
                tank->lastShootTime = currentTime;
                printf("Pew!\n");
            }
        }
    }

    if(tank->xPos < 0 )
    {
        tank->xPos = 0;
    }

    if(tank->xPos + tank->width > getCanvasWidth())
    {
        tank->xPos = getCanvasWidth() - tank->width;
    }
}

void renderTank(Tank * tank)
{
    SDL_Rect dst;
    dst.x = (int)tank->xPos;
    dst.y = (int)tank->yPos;
    dst.w = (int)tank->width;
    dst.h = (int)tank->height;

    SDL_RenderCopy(getRenderer(), tankTexture, NULL, &dst);
}