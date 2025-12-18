#include "bubakGroup.h"

BubakGroup createBubakGroup(int minDelayMs, int maxDelayMs, int paddingg, double bubakWidthh, double bubakHeightt)
{
    BubakGroup bubakGroup;

    bubakGroup.padding = paddingg;
    bubakGroup.minDelay = minDelayMs;
    bubakGroup.maxDelay = maxDelayMs;
    bubakGroup.currentDelay = maxDelayMs;
    bubakGroup.bubakWidth = bubakWidthh;
    bubakGroup.bubakHeight = bubakHeightt;

    double width = BUBAK_COLUMNS * bubakGroup.bubakWidth + (BUBAK_COLUMNS - 1) * bubakGroup.padding;
    double height = BUBAK_ROWS * bubakGroup.bubakHeight + (BUBAK_ROWS - 1) * bubakGroup.padding;
    double xStartingPosition = getCanvasWidth()/2 - width/2.0;
    double yStartingPosition = 200.0;

    for (int i = 0; i < BUBAK_GENERAL_ROWS; i++)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            double x = xStartingPosition + j * (bubakGroup.bubakWidth + bubakGroup.padding);
            double y = yStartingPosition + i * (bubakGroup.bubakHeight + bubakGroup.padding);

            bubakGroup.bubaks[i][j] = createBubak(x, y, bubakGroup.bubakWidth, bubakGroup.bubakHeight, BUBAK_TYPE_SOLIDER);
        }
    }
    
}


void updateBubakGroup(BubakGroup * bubakGroup)
{
    
}

void renderBubakGroup(BubakGroup * bubakGroup)
{
    for (int i = 0; i < BUBAK_ROWS; i++)
    {
        for (int j = 0; j < BUBAK_COLUMNS; j++)
        {
            renderBubak(&bubakGroup->bubaks[i][j]);
        }
    }   
}