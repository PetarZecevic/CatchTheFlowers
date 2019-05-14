#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

void init();
void drawSprite(int in_x, int in_y, int out_x, int out_y, int width, int height);
void drawMap();
void drawEndGame();
void printNum(int row,int column,int num);
void printCoins();
void insertItems();
void moveItems();
char getPressedKey();
void gameLoop();

#endif /* GAMEPLAY_H_ */
