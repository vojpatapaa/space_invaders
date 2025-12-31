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
#include "ui.h"
#include "eventFunctions.h"


SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * canvas;
SDL_Color background;

int running;
GamePart currentGamePart;

double desiredMaxMilPerFrame;
double deltaTime;
int desiredFPS;

MouseState mouseState;

/*Game objects*/
Tank playerTank;
BubakGroup enemyArmy;
Mix_Music * chopin;
Shield shield1;
Shield shield2;
Shield shield3;
Shield shield4;
Ufo ufo;

/*UI*/
Label * gameLabel;
Button * playButton;
Button * toggleDarkModeButton;
Button * exitGameButton;
Button * set120FpsButton;
Button * set60FpsButton;
Button * set30FpsButton;
Button * set20FpsButton;
Label * bestScoreLabel;
Label * bestScoreNumberLabel;
Label * currentScoreLabel;

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

int getWindowWidth()
{
    int width;
    SDL_GetWindowSize(window, &width, NULL);
    return width;
}


int getWindowHeight()
{
    int height;
    SDL_GetWindowSize(window, NULL, &height);
    return height;
}

int getCanvasWidth()
{
    return CANVAS_WIDTH;
}

int getCanvasHeight()
{
    return CANVAS_HEIGHT;
}

void setBackgroundColor(SDL_Color backgroundColor)
{
    background = backgroundColor;
}

SDL_Color getBackgroundColor()
{
    return background;
}

MouseState * getMouseState()
{
    return &mouseState;
}

SDL_Renderer * getRenderer()
{
    return renderer;
}

SDL_Window * get_window()
{
    return window;
}

void initGameSession()
{
    playerTank = createTank(getCanvasWidth()/4.0 * 2.35, CANVAS_HEIGHT-(8.0 * 2.5)-25, 13.0 * 2.5, 8.0 * 2.5, 1000);

    enemyArmy = createBubakGroup(50, 1000, 10, 35, 30);

    SDL_Color shieldColor = {0, 0, 255, 255};
    shield1 = createShield(getCanvasWidth()/4.0 * 0.35, 430.0, shieldColor);
    shield2 = createShield(getCanvasWidth()/4.0 * 1.35, 430.0, shieldColor);
    shield3 = createShield(getCanvasWidth()/4.0 * 2.35, 430.0, shieldColor);
    shield4 = createShield(getCanvasWidth()/4.0 * 3.35, 430.0, shieldColor);

    ufo = createUfo(0.0, 50.0, 50.0, 25, 10000, 200);

    setCurrentGamePart(GAME_PART_PLAY);

    setScore(0);
}

void initGameSessionWithoutTank()
{

    enemyArmy = createBubakGroup(50, 1000, 10, 35, 30);

    SDL_Color shieldColor = {0, 0, 255, 255};
    shield1 = createShield(getCanvasWidth()/4.0 * 0.35, 430.0, shieldColor);
    shield2 = createShield(getCanvasWidth()/4.0 * 1.35, 430.0, shieldColor);
    shield3 = createShield(getCanvasWidth()/4.0 * 2.35, 430.0, shieldColor);
    shield4 = createShield(getCanvasWidth()/4.0 * 3.35, 430.0, shieldColor);

    ufo = createUfo(0.0, 50.0, 50.0, 25, 10000, 200);

    setCurrentGamePart(GAME_PART_PLAY);

    setScore(0);
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

    if(SDL_SetHint(SDL_HINT_SHUTDOWN_DBUS_ON_QUIT, "1") == SDL_TRUE)
    {
        printf("yes");
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

    setRunning(1);
    setCurrentGamePart(GAME_PART_MENU);

    chopin = Mix_LoadMUS("assets/tank/sfx/chopin.wav");

    int loadedScore = loadScore();
    setScore(loadedScore);

    initUfoModule();
    initTankModule();
    initBubakModule();
    initProjectileModule();

    /*UI*/
    SDL_Color uiBackgroundColor = {59, 130, 246, 255};
    SDL_Color uiBackgroundHoverColor = {37, 99, 235, 255};
    SDL_Color uiTransparent = {255, 255, 255, 255};
    SDL_Color uiTextColor = {30, 64, 175, 255};

    gameLabel = createLabel(180, 0, 2.0, 2.0, "Space invaders", uiTextColor);
    playButton = createButton(30, 180, 200, 70, 0, "Play", uiTextColor, uiBackgroundColor, uiBackgroundHoverColor, initGameSession);
    toggleDarkModeButton = createButton(30, 255, 200, 70, 0, "Dark/white", uiTextColor, uiBackgroundColor, uiBackgroundHoverColor, toggleDarkModeEvent);
    exitGameButton = createButton(30, 330, 200, 70, 0, "Exit", uiTextColor, uiBackgroundColor, uiBackgroundHoverColor, endGameEvent);
    set120FpsButton = createButton(30, 430, 60, 40, 0, "120", uiTextColor, uiBackgroundColor, uiBackgroundHoverColor, set120FpsEvent);
    set60FpsButton  = createButton(100, 430, 60, 40, 0, "60", uiTextColor, uiBackgroundColor, uiBackgroundHoverColor, set60FpsEvent);
    set30FpsButton  = createButton(30, 480, 60, 40, 0, "30", uiTextColor, uiBackgroundColor, uiBackgroundHoverColor, set30FpsEvent);
    set20FpsButton  = createButton(100, 480, 60, 40, 0, "20", uiTextColor, uiBackgroundColor, uiBackgroundHoverColor, set20FpsEvent);
    bestScoreLabel = createLabel(450, 450, 1.0, 1.0, "Best Score: ", uiTextColor);
    char scoreBuffer[12];
    sprintf(scoreBuffer, "%d", getScore());
    bestScoreNumberLabel = createLabel(700, 450, 1.0, 1.0, scoreBuffer, uiTextColor);
    currentScoreLabel = createLabel(10.0, 10.0, 1.0, 1.0, "0", uiTextColor);


    mouseState.leftClicked = 0;
    mouseState.x = 0;
    mouseState.y = 0;


}

void handleInput()
{
    SDL_Event event;

    mouseState.leftClicked = 0;
    int screenPosX;
    int screenPosY;
    SDL_GetMouseState(&screenPosX, &screenPosY);
    mouseState.x = (double)screenPosX / (double)getWindowWidth() * (double)getCanvasWidth();
    mouseState.y = (double)screenPosY / (double)getWindowHeight() * (double)getCanvasHeight();

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                setRunning(0);
                break;

            case SDL_MOUSEBUTTONDOWN:
                    mouseState.leftClicked = 1;
                    break;

        }
    }
}

void update()
{
    int score;
    char buffer[20];

    switch (getCurrentGamePart())
    {
        case GAME_PART_MENU:
            updateButton(playButton);
            updateButton(toggleDarkModeButton);
            updateButton(exitGameButton);
            updateButton(set120FpsButton);
            updateButton(set60FpsButton);
            updateButton(set30FpsButton);
            updateButton(set20FpsButton);

            score = getScore();
            sprintf(buffer, "%d", score);
            updateLabelText(bestScoreNumberLabel, buffer);

            break;

        case GAME_PART_PLAY:
            updateTank(&playerTank);
            updateBubakGroup(&enemyArmy);
            updateProjectiles();
            updateShield(&shield1);
            updateShield(&shield2);
            updateShield(&shield3);
            updateShield(&shield4);

            score = getScore();
            sprintf(buffer, "Score: %d", score);
            updateLabelText(currentScoreLabel, buffer);

            updateUfo(&ufo);
            break;
       
        default:
            break;
    }

}

void render()
{
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_SetRenderTarget(renderer, canvas);
    SDL_RenderClear(renderer);

    /*tady bude rada na renderCopy*/
    switch (getCurrentGamePart())
    {
        case GAME_PART_MENU:
            renderLabel(gameLabel);
            renderButton(playButton);
            renderButton(toggleDarkModeButton);
            renderButton(exitGameButton);
            renderButton(set120FpsButton);
            renderButton(set60FpsButton);
            renderButton(set30FpsButton);
            renderButton(set20FpsButton);
            renderLabel(bestScoreLabel);
            renderLabel(bestScoreNumberLabel);
            break;

        case GAME_PART_PLAY:
            renderTank(&playerTank);
            renderBubakGroup(&enemyArmy);
            renderProjectiles();
            renderShield(&shield1);
            renderShield(&shield2);
            renderShield(&shield3);
            renderShield(&shield4);
            renderLabel(currentScoreLabel);
            renderUfo(&ufo);
            break;
        
        default:
            break;
    }


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