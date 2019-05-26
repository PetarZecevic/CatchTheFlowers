#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "render.h"

void drawMap();
void drawEndGame();
void printNum(int row,int column,int num);
void printCoins();
void insertItems();
void moveItems();
char getPressedKey();
void gameLoop();

#endif /* GAMEPLAY_H_ */
