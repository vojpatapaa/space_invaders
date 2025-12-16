//
// Created by Intel on 14/12/2025.
//

#include "textureManager.h"

SDL_Texture * createTextureFromImage(const char * path)
{
    SDL_Surface * surface = IMG_Load(path);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
    SDL_FreeSurface(surface);
    return texture;
}


SDL_Texture * createCanvasTexture(int width, int height)
{
    SDL_Texture * texture = SDL_CreateTexture(getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    return texture;
}
