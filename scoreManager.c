#include "scoreManager.h"
#include <stdio.h>

char * SCORE_PATH = "score.dat";
int score;

void setScore(int newScore)
{
    score = newScore;
}

void addToScore(int add)
{
    score += add;
}

int getScore()
{
    return score;
}

void saveScore()
{
    FILE * file = NULL;
    
    file = fopen(SCORE_PATH, "wb");
    if(file == NULL)
    {
        return;
    }

    fwrite(&score, sizeof(score), 1, file);


    fclose(file);
}


int loadScore()
{
    FILE * file = NULL;
    int buffer = 0;
    
    file = fopen(SCORE_PATH, "rb");
    if(file == NULL)
    {
        return 0;
    }

    fread(&buffer, sizeof(buffer), 1, file);
    fclose(file);

    return buffer;
}