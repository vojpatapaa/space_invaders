#include "ui.h"
#include "textureManager.h"
#include <stdlib.h>

const char * FONT_PATH = "assets/fonts/Cascadia.ttf";

Label * createLabel(double x, double y, int width, int height, int padding, char * text, SDL_Color textColor, SDL_Color backgroundColor)
{
    Label * label = (Label *)malloc(sizeof(label));
    if(label == NULL)
    {
        return NULL;
    }

    label->xPos = x;
    label->yPos = y;
    label->width = width;
    label->height = height;
    label->padding = padding;
    label->backgroundColor = backgroundColor;
    label->textColor = textColor;

    label->textTexture = createTextureFromText(text, FONT_PATH, width-padding, height-padding, textColor);

    return label;
}

void updateLabelText(Label * label, char * text)
{
    SDL_DestroyTexture(label->textTexture);
    label->textTexture = createTextureFromText(text, FONT_PATH, label->width - label->padding, label->height - label->padding, label->textColor);
}

void renderLabel(Label * label)
{
    SDL_Rect labelDst;
    SDL_Rect textDst;

    labelDst.x = (int)label->xPos;
    labelDst.y = (int)label->yPos;
    labelDst.w = label->width;
    labelDst.h = label->height;

    textDst.x = (int)(label->xPos + label->padding);
    textDst.y = (int)(label->yPos + label->padding);
    textDst.w = label->width - label->padding;
    textDst.h = label->height - label->padding;

    SDL_SetRenderDrawColor(getRenderer(), label->backgroundColor.r, label->backgroundColor.g, label->backgroundColor.b, 255);
    SDL_RenderFillRect(getRenderer(), &labelDst);
    SDL_RenderCopy(getRenderer(), label->textTexture, NULL, &textDst);
}

void destroyLabel(Label * label)
{
    SDL_DestroyTexture(label->textTexture);
    free(label);
}


Button * createButton(double x, double y, int width, int height, int padding, char * text, SDL_Color textColor, SDL_Color backgroundColor, SDL_Color secondaryBackgroundColor, void (*onClickAction)(void))
{
    Button * button = (Button *)malloc(sizeof(button));
    if(button == NULL)
    {
        return NULL;
    }

    button->xPos = x;
    button->yPos = y;
    button->width = width;
    button->height = height;
    button->padding = padding;
    button->backgroundColor = backgroundColor;
    button->secondaryBackgroundColor = secondaryBackgroundColor;
    button->textColor = textColor;
    button->onClickAction = onClickAction;

    return button;
}

void updateButton(Button * button);
void renderButton(Button * button);
void destroyButton(Button * button);