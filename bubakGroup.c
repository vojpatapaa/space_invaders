#include "bubakGroup.h"
#include "projectile.h"
#include "scoreManager.h"

Mix_Chunk * bubakShoot;
const char * BUBAK_SHOOT_SFX_PATH = "assets/bubak/sfx/bubak_shoot.wav";

int getAliveBubaks(BubakGroup * bubakGroup)
{
    int aliveCount = 0;
    for (int i = 0; i < BUBAK_ROWS; i++)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            if(bubakGroup->bubaks[i][j].alive)
            {
                aliveCount++;
            }
        }
        
    }
    
    return aliveCount;

}

Bubak * getLeadingRightBubak(BubakGroup * bubakGroup)
{
    for (int j = BUBAK_COLUMNS - 1; j >= 0; j--)
    {
        for (int i = 0; i < BUBAK_ROWS; i++)
        {
            if(bubakGroup->bubaks[i][j].alive)
            {
                return &bubakGroup->bubaks[i][j];
            }
        }   
    }

    return NULL;
    
}

Bubak * getLeadingLeftBubak(BubakGroup * bubakGroup)
{
    for (int j = 0; j < BUBAK_COLUMNS; j++)
    {
        for (int i = 0; i < BUBAK_ROWS; i++)
        {
            if(bubakGroup->bubaks[i][j].alive)
            {
                return &bubakGroup->bubaks[i][j];
            }
        }   
    }

    return NULL;
}

void initBubakGroupModule()
{
    bubakShoot = Mix_LoadWAV(BUBAK_SHOOT_SFX_PATH);
}

void quitBubakGroupModule()
{
    Mix_FreeChunk(bubakShoot);
}

BubakGroup createBubakGroup(int minDelayMs, int maxDelayMs, int paddingg, int bubakWidthh, int bubakHeightt)
{
    BubakGroup bubakGroup;

    bubakGroup.direction = RIGHT;
    bubakGroup.padding = paddingg;
    bubakGroup.minDelay = minDelayMs;
    bubakGroup.maxDelay = maxDelayMs;
    bubakGroup.currentDelay = maxDelayMs;
    bubakGroup.bubakWidth = bubakWidthh;
    bubakGroup.bubakHeight = bubakHeightt;
    

    int width = BUBAK_COLUMNS * bubakGroup.bubakWidth + (BUBAK_COLUMNS - 1) * bubakGroup.padding;
    int height = BUBAK_ROWS * bubakGroup.bubakHeight + (BUBAK_ROWS - 1) * bubakGroup.padding;
    double xStartingPosition = getCanvasWidth()/2 - width/2.0;
    double yStartingPosition = 100.0;

    bubakGroup.lastUpdateTime = SDL_GetPerformanceCounter();

    int i;
    for (i = 0; i < BUBAK_GENERAL_ROWS; i++)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            double x = xStartingPosition + j * (bubakGroup.bubakWidth + bubakGroup.padding);
            double y = yStartingPosition + i * (bubakGroup.bubakHeight + bubakGroup.padding);

            bubakGroup.bubaks[i][j] = createBubak(x, y, bubakGroup.bubakWidth, bubakGroup.bubakHeight, BUBAK_TYPE_GENERAL);
        }
    }

    while (i < BUBAK_COMMANDER_ROWS + BUBAK_GENERAL_ROWS)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            double x = xStartingPosition + j * (bubakGroup.bubakWidth + bubakGroup.padding);
            double y = yStartingPosition + i * (bubakGroup.bubakHeight + bubakGroup.padding);

            bubakGroup.bubaks[i][j] = createBubak(x, y, bubakGroup.bubakWidth, bubakGroup.bubakHeight, BUBAK_TYPE_COMMANDER);
        }

        i++;
    }

    while (i < BUBAK_COMMANDER_ROWS + BUBAK_GENERAL_ROWS + BUBAK_TYPE_SOLIDER)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            double x = xStartingPosition + j * (bubakGroup.bubakWidth + bubakGroup.padding);
            double y = yStartingPosition + i * (bubakGroup.bubakHeight + bubakGroup.padding);

            bubakGroup.bubaks[i][j] = createBubak(x, y, bubakGroup.bubakWidth, bubakGroup.bubakHeight, BUBAK_TYPE_SOLIDER);
        }

        i++;
    }

    return bubakGroup;
    
}


void updateBubakGroup(BubakGroup * bubakGroup)
{
    int aliveBubaks = getAliveBubaks(bubakGroup);
    Uint64 currentTime = SDL_GetPerformanceCounter();
    Bubak * leadingBubak;
    double moveSpeed;
    double elapsedTime;
    double elapsedRounds;

    bubakGroup->currentDelay = bubakGroup->minDelay + ((aliveBubaks - 1)/(double)(BUBAK_COLUMNS * BUBAK_ROWS)) * (bubakGroup->maxDelay - bubakGroup->minDelay);
    elapsedTime = (currentTime - bubakGroup->lastUpdateTime) / (double)SDL_GetPerformanceFrequency() * 1000;

    //Turning off the game
    if(aliveBubaks == 0)
    {
        int score = getScore();
        if(score > loadScore())
        {
            setScore(score);
            saveScore();
        }
        initGameSessionWithoutTank();
        //initMenuSession();
        return;
    }
    

    //Updating only after certain ammount of time passed
    if(elapsedTime >= bubakGroup->currentDelay)
    {
        elapsedRounds = elapsedTime/bubakGroup->currentDelay;
        bubakGroup->lastUpdateTime = currentTime;

        //SETTING EXPLODED TO DEAD (for rendering)
        for (int i = 0; i < BUBAK_ROWS; i++)
        {
            for (int j = 0; j < BUBAK_COLUMNS; j++)
            {
                if(bubakGroup->bubaks[i][j].type == BUBAK_TYPE_EXPLODED)
                {
                    bubakGroup->bubaks[i][j].type = BUBAK_TYPE_DEAD;
                }
            }
            
        }

        //Moving
        switch (bubakGroup->direction)
        {
            case RIGHT:
            moveSpeed = BUBAK_HORIZONTAL_SPEED;
            leadingBubak = getLeadingRightBubak(bubakGroup);
                if(getBubakRightPos(leadingBubak) + BUBAK_HORIZONTAL_SPEED * elapsedRounds > getCanvasWidth())
                {
                    bubakGroup->direction = DOWN;
                    moveSpeed = getCanvasWidth() - bubakGroup->bubakWidth - leadingBubak->xPos;
                }
                else
                {
                    moveSpeed = BUBAK_HORIZONTAL_SPEED * elapsedRounds;
                }

                for (int i = 0; i < BUBAK_ROWS; i++)
                {
                    for (int j = 0; j < BUBAK_COLUMNS; j++)
                    {
                        moveSpritePositionRight(&bubakGroup->bubaks[i][j]);
                        bubakGroup->bubaks[i][j].xPos += moveSpeed;
                    }
                    
                }
                break;

            case DOWN:
                moveSpeed = BUBAK_VERTICAL_SPEED;
                leadingBubak = getLeadingLeftBubak(bubakGroup);
                if(leadingBubak->xPos == 0.0)
                {
                    bubakGroup->direction = RIGHT;
                }
                else
                {
                    bubakGroup->direction = LEFT;
                }

                for (int i = 0; i < BUBAK_ROWS; i++)
                {
                    for (int j = 0; j < BUBAK_COLUMNS; j++)
                    {
                        moveSpritePositionRight(&bubakGroup->bubaks[i][j]);
                        bubakGroup->bubaks[i][j].yPos += moveSpeed;
                    }
                    
                }
                break;

            case LEFT:
            moveSpeed = BUBAK_HORIZONTAL_SPEED;
                leadingBubak = getLeadingLeftBubak(bubakGroup);
                if(getBubakLeftPos(leadingBubak) - BUBAK_HORIZONTAL_SPEED * elapsedRounds < 0)
                {
                    bubakGroup->direction = DOWN;
                    moveSpeed = -leadingBubak->xPos;
                }
                else
                {
                    moveSpeed = -BUBAK_HORIZONTAL_SPEED * elapsedRounds;
                }

                for (int i = 0; i < BUBAK_ROWS; i++)
                {
                    for (int j = 0; j < BUBAK_COLUMNS; j++)
                    {
                        moveSpritePositionRight(&bubakGroup->bubaks[i][j]);
                        bubakGroup->bubaks[i][j].xPos += moveSpeed;
                    }
                    
                }
                break;

            
            default:
                break;
        }

        //random shooting
        int randomCount = rand()%(aliveBubaks - 1 + 1) + 1;
        
        for (int i = 0; i < BUBAK_ROWS; i++)
        {
            for (int j = 0; j < BUBAK_COLUMNS && randomCount > 0; j++)
            {
                int random = rand()%(100-0+1) + 0;
                if(random >= 99 && bubakGroup->bubaks[i][j].alive)
                {
                    randomCount--;
                    
                    double x = (int)bubakGroup->bubaks[i][j].xPos + bubakGroup->bubakWidth/2.0;
                    double y = (int)bubakGroup->bubaks[i][j].yPos + bubakGroup->bubakHeight;
                    createProjectile(x, y, BUBAK_PROJECTILE_WIDTH, BUBAK_PROJECTILE_HEIGHT, PROJECTILE_TYPE_ENEMY, BUBAK_PROJECTILE_SPEED);
                    Mix_PlayChannel(-1, bubakShoot, 0);
                }
            }
            
        }
        
        
    }

    //calling updateBubak
    for (int i = 0; i < BUBAK_ROWS; i++)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            updateBubak(&bubakGroup->bubaks[i][j]);
        }
        
    } 
}

void renderBubakGroup(BubakGroup * bubakGroup)
{
    for (int i = 0; i < BUBAK_ROWS; i++)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            renderBubak(&bubakGroup->bubaks[i][j]);
        }
    }
}