#ifndef SPACE_INVADERS_SCORE_MANAGER_H
#define SPACE_INVADERS_SCORE_MANAGER_H

void setScore(int newScore);
void addToScore(int add);
int getScore();

void saveScore();
int loadScore();


#endif