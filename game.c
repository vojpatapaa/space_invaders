#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

#define CANVAS_WIDTH 960
#define CANVAS_HEIGHT 540

#include "game.h"
#include "tank.h"
#include "bubakGroup.h"
#include "projectile.h"
#include "shield.h"
#include "ufo.h"
#include "scoreManager.h"


SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * canvas;
SDL_Color background;

int running;
GamePart currentGamePart;

double desiredMaxMilPerFrame;
double deltaTime;
int desiredFPS;

/*Game objects*/
Tank playerTank;
BubakGroup enemyArmy;
Mix_Music * chopin;
Shield shield1;
Shield shield2;
Shield shield3;
Shield shield4;
Ufo ufo;


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

GamePart getCurrentGamePart()
{
    return currentGamePart;
}

void setCurrentGamePart(GamePart gamePart)
{
    currentGamePart = gamePart;
}

void setRunning(int newRunning)
{
    running = newRunning;
}

int isRunning()
{
    return running;
}

int getCanvasWidth()
{
    return CANVAS_WIDTH;
}

int getCanvasHeight()
{
    return CANVAS_HEIGHT;
}

SDL_Renderer * getRenderer()
{
    return renderer;
}

SDL_Window * get_window()
{
    return window;
}

void initGame(const char * windowLabel, int winWidth, int winHeight, int initialFPS, SDL_Color backgroundColor)
{

    if (SDL_Init(SDL_INIT_EVERYTHING))
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
        IMG_Quit();
        TTF_Quit();
        Mix_Quit();
        exit(-1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL)
    {
        printf("%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        Mix_Quit();
        exit(-1);
    }

    setDesiredFPS(initialFPS);

    background = backgroundColor;
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    canvas = createCanvasTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
    if (canvas == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        Mix_Quit();
        exit(-1);
    }

    running = 1;
    currentGamePart = GAME_PART_PLAY;

    initTankModule();
    playerTank = createTank(CANVAS_WIDTH/2 - (13.0/2.5), CANVAS_HEIGHT-(8.0 * 2.5)-25, 13.0 * 2.5, 8.0 * 2.5, 1000);

    initBubakModule();
    enemyArmy = createBubakGroup(50, 1000, 10, 35, 30);

    initProjectileModule();

    SDL_Color shieldColor = {0, 0, 255, 255};
    shield1 = createShield(getCanvasWidth()/4.0 * 0.35, 430.0, shieldColor);
    shield2 = createShield(getCanvasWidth()/4.0 * 1.35, 430.0, shieldColor);
    shield3 = createShield(getCanvasWidth()/4.0 * 2.35, 430.0, shieldColor);
    shield4 = createShield(getCanvasWidth()/4.0 * 3.35, 430.0, shieldColor);

    initUfoModule();
    ufo = createUfo(0.0, 50.0, 50, 25, 10000, 200);

    chopin = Mix_LoadMUS("assets/tank/sfx/chopin.wav");

    int loadedScore = loadScore();
    if(loadedScore == -1)
    {
        setScore(0);
    }

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

            case SDL_MOUSEBUTTONDOWN:
                    Mix_FadeInMusicPos(chopin, 0, 10000, 5.0);
                    break;

        }
    }
    

}

void update()
{
    updateTank(&playerTank);
    updateBubakGroup(&enemyArmy);
    updateProjectiles();
    updateShield(&shield1);
    updateShield(&shield2);
    updateShield(&shield3);
    updateShield(&shield4);
    updateUfo(&ufo);
}

void render()
{
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_SetRenderTarget(renderer, canvas);
    SDL_RenderClear(renderer);

    /*tady bude rada na renderCopy*/
    renderTank(&playerTank);
    renderBubakGroup(&enemyArmy);
    renderProjectiles();
    renderShield(&shield1);
    renderShield(&shield2);
    renderShield(&shield3);
    renderShield(&shield4);
    renderUfo(&ufo);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, canvas, NULL, NULL);
    SDL_RenderPresent(renderer);

}

void clearGame()
{

    Mix_FreeMusic(chopin);

    quitUfoModule();
    quitProjectileModule();
    quitBubakModule();
    quitTankModule();

    SDL_DestroyTexture(canvas);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}