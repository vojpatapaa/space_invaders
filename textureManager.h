#ifndef SPACE_INVADERS_TEXTUREMANAGER_H
#define SPACE_INVADERS_TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

typedef struct 
{
    int width;
    int height;
    int boxWidth;
    int boxHeight;
    int boxCount;
    SDL_Texture * texture;

}SpriteSheet;

SDL_Texture * createTextureFromImage(const char * path);
SDL_Texture * createTextureFromText(const char * str, char * fontPath, SDL_Color color);
SDL_Texture * createCanvasTexture(int width, int height);

SpriteSheet * createSpriteSheet(const char * path, int boxWidthh, int boxHeightt, int boxCountt);
void destroySpriteSheet(SpriteSheet * spriteSheet);

#endif