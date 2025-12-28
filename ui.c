#include "ui.h"
#include "textureManager.h"
#include <stdlib.h>

char * FONT_PATH = "assets/fonts/Cascadia.ttf";

Label * createLabel(double x, double y, int width, int height, int padding, char * text, SDL_Color textColor, SDL_Color backgroundColor)
{
    Label * label = (Label *)malloc(sizeof(Label));
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

    SDL_SetRenderDrawColor(getRenderer(), label->backgroundColor.r, label->backgroundColor.g, label->backgroundColor.b, label->backgroundColor.a);
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
    Button * button = (Button *)malloc(sizeof(Button));
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

void updateButton(Button * button)
{
   MouseState * mouse =  getMouseState();
   SDL_Point point;
   SDL_Rect buttonRect;

   point.x = mouse->x;
   point.y = mouse->y;

   buttonRect.x = (int)button->xPos;
   buttonRect.y = (int)button->yPos;
   buttonRect.w = button->width;
   buttonRect.h = button->height;

   button->hovered = 0;

   if(SDL_PointInRect(&point, &buttonRect))
   {

    button->hovered = 1;

    if(mouse->leftClicked)
    {
        button->onClickAction();
    }

   }
}

void renderButton(Button * button)
{

    SDL_Rect buttonDst;
    SDL_Rect textDst;

    buttonDst.x = (int)button->xPos;
    buttonDst.y = (int)button->yPos;
    buttonDst.w = button->width;
    buttonDst.h = button->height;

    textDst.x = (int)(button->xPos + button->padding);
    textDst.y = (int)(button->yPos + button->padding);
    textDst.w = button->width  - (button->padding * 2);
    textDst.h = button->height - (button->padding * 2);

    switch (button->hovered)
    {
        case 0:
            SDL_SetRenderDrawColor(getRenderer(), button->secondaryBackgroundColor.r, button->secondaryBackgroundColor.g, button->secondaryBackgroundColor.b, button->secondaryBackgroundColor.a);
            SDL_RenderFillRect(getRenderer(), &buttonDst);
            SDL_RenderCopy(getRenderer(), button->textTexture, NULL, &textDst);
            break;

        case 1:
            SDL_SetRenderDrawColor(getRenderer(), button->secondaryBackgroundColor.r, button->secondaryBackgroundColor.g, button->secondaryBackgroundColor.b, button->secondaryBackgroundColor.a);
            SDL_RenderFillRect(getRenderer(), &buttonDst);
            SDL_RenderCopy(getRenderer(), button->textTexture, NULL, &textDst);
            break;
        
        default:
            break;
    }
}


void destroyButton(Button * button)
{
    SDL_DestroyTexture(button->textTexture);
    free(button);
}