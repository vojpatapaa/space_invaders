#ifndef SPACE_UI_H
#define SPACE_UI_H

#include "SDL2/SDL.h"

typedef struct
{
    double xPos;
    double yPos;
    int width;
    int height;
    int padding;
    SDL_Color textColor;
    SDL_Color backgroundColor;
    SDL_Texture * textTexture;
}Label;

Label * createLabel(double x, double y, int width, int height, int padding, char * text, SDL_Color textColor, SDL_Color backgroundColor);
void updateLabelText(Label * label, char * text);
void renderLabel(Label * label);
void destroyLabel(Label * label);

typedef struct
{
    double xPos;
    double yPos;
    int width;
    int height;
    int padding;
    SDL_Color textColor;
    SDL_Color backgroundColor;
    SDL_Color secondaryBackgroundColor;
    SDL_Texture * textTexture;
    int hovered;

    void (*onClickAction)(void);
}Button;

Button * createButton(double x, double y, int width, int height, int padding, char * text, SDL_Color textColor, SDL_Color backgroundColor, SDL_Color secondaryBackgroundColor, void (*onClickAction)(void));
void updateButton(Button * button);
void renderButton(Button * button);
void destroyButton(Button * button);




#endif