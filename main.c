#include <stdio.h>
#include "game.h"

int main(int argc, char ** argv)
{
    initGame("Space invaders", 960, 800);

    Uint64 lastTime = SDL_GetPerformanceCounter();
    while (isRunning())
    {
        Uint64 currentTime = SDL_GetPerformanceCounter();
        setDeltaTime((currentTime - lastTime) / (double)SDL_GetPerformanceFrequency());
        lastTime = currentTime;

        handleInput();
        update();
        render();

        Uint64 frameEnd = SDL_GetPerformanceCounter();
        double elapsedMili = (frameEnd - currentTime) / (double)SDL_GetPerformanceFrequency() * 1000.0;
        if (elapsedMili < getDesiredMaxMilPerFrame())
        {
            SDL_Delay(getDesiredMaxMilPerFrame() - elapsedMili);
        }

    }
    clearGame();

    printf("test");

    return 0;
}
