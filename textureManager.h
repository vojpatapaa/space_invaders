#ifndef SPACE_INVADERS_TEXTUREMANAGER_H
#define SPACE_INVADERS_TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

SDL_Texture * createTextureFromImage(const char * path);
SDL_Texture * createTextureFromText(const char * str, TTF_Font font, int width, int height);
SDL_Texture * createCanvasTexture(int width, int height);

#endif //SPACE_INVADERS_TEXTUREMANAGER_H