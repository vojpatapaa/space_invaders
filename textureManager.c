#include "textureManager.h"

SDL_Texture * createTextureFromImage(const char * path)
{
    SDL_Surface * surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("Could not find load the image: %s\n", path);
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture * createTextureFromText(const char * str, char * fontPath, SDL_Color color)
{
    SDL_Surface * surface = NULL;
    SDL_Texture * texture = NULL;
    TTF_Font * font = TTF_OpenFont(fontPath, 24);

    if(font == NULL)
    {
        return NULL;
    }

    surface = TTF_RenderText_Solid(font, str, color);
    if(surface == NULL)
    {
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
    if(texture == NULL)
    {
        SDL_FreeSurface(surface);
        return NULL;
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    return texture;
}


SDL_Texture * createCanvasTexture(int width, int height)
{
    SDL_Texture * texture = SDL_CreateTexture(getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    return texture;
}

SpriteSheet * createSpriteSheet(const char * path, int boxWidthh, int boxHeightt, int boxCountt)
{
    SpriteSheet * spriteSheet = (SpriteSheet *)malloc(sizeof(SpriteSheet));
    if(spriteSheet == NULL)
    {
        return NULL;
    }

    spriteSheet->texture = createTextureFromImage(path);
    if(spriteSheet->texture == NULL)
    {
        printf("Could not find load the image: %s\n", path);
        free(spriteSheet);
        return NULL;
    }

    spriteSheet->boxWidth = boxWidthh;
    spriteSheet->boxHeight = boxHeightt;
    spriteSheet->boxCount = boxCountt;

    SDL_QueryTexture(spriteSheet->texture, NULL, NULL, &spriteSheet->width, &spriteSheet->height);

    return spriteSheet;
}


void destroySpriteSheet(SpriteSheet * spriteSheet)
{
    if(spriteSheet != NULL)
    {
        if(spriteSheet->texture != NULL)
        {
            SDL_DestroyTexture(spriteSheet->texture);
        }
        free(spriteSheet);
    }
}
