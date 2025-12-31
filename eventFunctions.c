#include "eventFunctions.h"

void startActualGameEvent()
{
    setCurrentGamePart(GAME_PART_PLAY);
}

void toggleDarkModeEvent()
{
    SDL_Color color = getBackgroundColor();
    if(color.r == 255 && color.g == 255 && color.b == 255 && color.a == 255)
    {
        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = 255;
        setBackgroundColor(color);
    }
    else
    {
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
        setBackgroundColor(color);
    }
}

void initMenu()
{

}

void set120FpsEvent()
{
    setDesiredFPS(120);
}

void set60FpsEvent()
{
    setDesiredFPS(60);
}

void set30FpsEvent()
{
    setDesiredFPS(30);
}

void set20FpsEvent()
{
    setDesiredFPS(20);
}

void endGameEvent()
{
    setRunning(0);
}