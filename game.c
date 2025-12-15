//
// Created by Intel on 11/12/2025.
//

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

#define CANVAS_WIDTH 960
#define CANVAS_HEIGHT 540

#include "game.h"


SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * canvas;

const int screenHeight = SCREEN_HEIGHT;
const int screenWidth = SCREEN_WIDTH;

int running;

double desiredMaxMilPerFrame;
double deltaTime;
int desiredFPS;

void setDesiredFPS(int fps)
{
    desiredFPS = fps;
    desiredMaxMilPerFrame = 1000.0f/(double)desiredFPS;
}

int getDesiredFPS()
{
    return desiredFPS;
}

double getDesiredMaxMilPerFrame()
{
    return desiredMaxMilPerFrame;
}

void setDeltaTime(double delta)
{
    deltaTime = delta;
}

double getDeltaTime()
{
    return deltaTime;
}

void setRunning(int newRunning)
{
    running = newRunning;
}

int isRunning()
{
    return running;
}

SDL_Renderer * getRenderer()
{
    return renderer;
}

SDL_Window * get_window()
{
    return window;
}

void initGame(const char *windowLabel, int winWidth, int winHeight)
{

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("%s\n", SDL_GetError());
        exit(-1);
    }

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_Quit();
        printf("%s\n", IMG_GetError() );
        exit(-1);
    }

    if (TTF_Init() == -1)
    {
        SDL_Quit();
        IMG_Quit();
        printf("%s\n", TTF_GetError());
        exit(-1);
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )
    {
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        printf("%s\n", Mix_GetError());
        exit(-1);
    }

    window = SDL_CreateWindow(windowLabel, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        printf("%s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL)
    {
        printf("%s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    setDesiredFPS(60);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    canvas = createCanvasTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
    if (canvas == NULL)
    {
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        Mix_Quit();
    }

    running = 1;
}

void handleInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                setRunning(0);
                break;

            default:
                break;
        }
    }
}

void update()
{

}

void render()
{
    SDL_SetRenderTarget(renderer, canvas);
    SDL_RenderClear(renderer);
    /*tady bude rada na renderCopy*/

    /*Jenom Test*/
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {200, 200, 100, 150};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    /*Jenom test*/

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, canvas, NULL, NULL);
    SDL_RenderPresent(renderer);

}

void clearGame()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(canvas);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}
