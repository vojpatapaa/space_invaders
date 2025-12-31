#include "ui.h"
#include "textureManager.h"
#include <stdlib.h>

char * FONT_PATH = "assets/fonts/moby.monospace.ttf";

Label * createLabel(double x, double y, double widthScale, double heightScale, char * text, SDL_Color textColor)
{
    Label * label = (Label *)malloc(sizeof(Label));
    if(label == NULL)
    {
        return NULL;
    }

    label->xPos = x;
    label->yPos = y;
    label->width = widthScale;
    label->height = heightScale;
    label->textColor = textColor;

    label->textTexture = createTextureFromText(text, FONT_PATH, textColor);
    return label;
}

void updateLabelText(Label * label, char * text)
{
    SDL_DestroyTexture(label->textTexture);
    label->textTexture = createTextureFromText(text, FONT_PATH, label->textColor);
}

void renderLabel(Label * label)
{
    SDL_Rect textDst;
    int texWidth;
    int texHeight;
    SDL_QueryTexture(label->textTexture, NULL, NULL, &texWidth, &texHeight);

    textDst.x = (int)(label->xPos);
    textDst.y = (int)(label->yPos);
    textDst.w = label->width * texWidth;
    textDst.h = label->height * texHeight;

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
    button->backgroundColor = backgroundColor;
    button->secondaryBackgroundColor = secondaryBackgroundColor;
    button->textColor = textColor;
    button->onClickAction = onClickAction;

    button->textTexture = createTextureFromText(text, FONT_PATH, button->textColor);

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

    textDst.x = (int)(button->xPos);
    textDst.y = (int)(button->yPos);
    textDst.w = button->width;
    textDst.h = button->height;

    switch (button->hovered)
    {
        case 1:
            SDL_SetRenderDrawColor(getRenderer(), button->secondaryBackgroundColor.r, button->secondaryBackgroundColor.g, button->secondaryBackgroundColor.b, button->secondaryBackgroundColor.a);
            SDL_RenderFillRect(getRenderer(), &buttonDst);
            SDL_RenderCopy(getRenderer(), button->textTexture, NULL, &textDst);
            break;

        case 0:
            SDL_SetRenderDrawColor(getRenderer(), button->backgroundColor.r, button->backgroundColor.g, button->backgroundColor.b, button->backgroundColor.a);
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