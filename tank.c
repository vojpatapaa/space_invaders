#include "tank.h"
#include "projectile.h"
#include "scoreManager.h"
#include "ui.h"

#define MOVE_SPEED 250.0

#define LIFE_LINE_WIDTH 90
#define LIFE_LINE_HEIGHT 10

SDL_Color uiTextColor = {30, 64, 175, 255};
SDL_Texture * tankTexture = NULL;
const char * TANK_TEXTURE_PATH = "assets/tank/textures/tank.png";
Label * lifesLabel;
Mix_Chunk * tankDamage;
const char * TANK_DAMAGE_PATH = "assets/tank/sfx/tank_damage.wav";
Mix_Chunk * tankLaserShot;
const char * TANK_LASER_SHOT_PATH = "assets/tank/sfx/tank_laser_shot.wav";


void initTankModule()
{
    tankTexture = createTextureFromImage(TANK_TEXTURE_PATH);
    lifesLabel = createLabel(930.0, 10.0, 1.2, 1.2, "3", uiTextColor);
    tankDamage = Mix_LoadWAV(TANK_DAMAGE_PATH);
    tankLaserShot = Mix_LoadWAV(TANK_LASER_SHOT_PATH);
}

void quitTankModule()
{
    Mix_FreeChunk(tankLaserShot);
    Mix_FreeChunk(tankDamage);
    destroyLabel(lifesLabel);
    SDL_DestroyTexture(tankTexture);
}

Tank createTank(double x, double y, int tankWidth, int tankHeight, int miliShootDelay)
{
    Tank tank;

    tank.DelayTime = miliShootDelay;
    tank.lastShootTime = 0;
    tank.lives = 3;

    tank.xPos = x;
    tank.yPos = y;
    tank.width = tankWidth;
    tank.height = tankHeight;
    tank.activeInput = 1;


    return tank;
}

void updateTank(Tank * tank, BubakGroup * bubakGroup)
{
    //ovladani pomoci vstupu
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
                createProjectile(tank->xPos + tank->width/2.0, tank->yPos, TANK_PROJECTILE_WIDTH, TANK_PROJECTILE_HEIGHT, PROJECTILE_TYPE_TANK, TANK_PROJECTILE_SPEED);
                Mix_PlayChannel(-1, tankLaserShot, 0);
            }
        }
    }

    //kolize s nepratelkskymi strelami && bubaky
    SDL_Rect tankDst;
    SDL_Rect shotDst;
    SDL_Rect bubakDst;
    dynarray * shots = getShots();
    int count = shots->size;

    tankDst.x = (int)tank->xPos;
    tankDst.y = (int)tank->yPos;
    tankDst.w = tank->width;
    tankDst.h = tank->height;

    for (int i = 0; i < count; i++)
    {
        Projectile * projectile = shots->items[i];
        shotDst.x = (int)projectile->xPos;
        shotDst.y = (int)projectile->yPos;
        shotDst.w = projectile->width;
        shotDst.h = projectile->height;

        if(projectile->type == PROJECTILE_TYPE_ENEMY && SDL_HasIntersection(&tankDst, &shotDst))
        {
            tank->lives = tank->lives - 1;
            destroyProjectile(projectile);
            Mix_PlayChannel(-1, tankDamage, 0);
            break;
        }
    }

    for (int i = 0; i < BUBAK_ROWS; i++)
    {
        int broken = 0;
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            Bubak bubak = bubakGroup->bubaks[i][j];
            bubakDst.x = (int)bubak.xPos;
            bubakDst.y = (int)bubak.yPos;
            bubakDst.w = bubak.width;
            bubakDst.h = bubak.height;

            if(bubak.type != BUBAK_TYPE_DEAD && bubak.type != BUBAK_TYPE_EXPLODED && SDL_HasIntersection(&bubakDst, &tankDst))
            {
                tank->lives = 0;
                broken = 1;
                break;
            }
        }

        if(broken)
        {
            break;
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

    if(tank->lives == 0)
    {
        int biggestScore = loadScore();
        if(getScore() > biggestScore)
        {
            saveScore();
        }
        setCurrentGamePart(GAME_PART_MENU);
        initMenuSession();
    }

    char buffer[20];
    sprintf(buffer, "%d", tank->lives);
    updateLabelText(lifesLabel, buffer);
}

void renderTank(Tank * tank)
{
    SDL_Rect dst;
    dst.x = (int)tank->xPos;
    dst.y = (int)tank->yPos;
    dst.w = tank->width;
    dst.h = tank->height;

    SDL_RenderCopy(getRenderer(), tankTexture, NULL, &dst);

    SDL_Rect lineDst;
    lineDst.w = LIFE_LINE_WIDTH;
    lineDst.h = LIFE_LINE_HEIGHT;
    lineDst.y = getCanvasHeight() - 5;
    lineDst.x = 5;
    SDL_SetRenderDrawColor(getRenderer(), uiTextColor.r, uiTextColor.g, uiTextColor.b, 255);
    for (int i = 0; i < tank->lives; i++)
    {
        SDL_RenderFillRect(getRenderer(), &lineDst);
        lineDst.x += LIFE_LINE_WIDTH + 5;
    }

    renderLabel(lifesLabel);
    
}