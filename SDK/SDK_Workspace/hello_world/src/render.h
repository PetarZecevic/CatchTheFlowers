#ifndef RENDER_H_
#define RENDER_H_

#include "bunny.h"
#include "sprite.h"
#include "object.h"

// We consider row and column as sprite of dimension 16x16.
void drawBackgroundSprite(unsigned int row, unsigned int column, const BackgroundSprite background);
void drawBunny(Bunny* bunny);
void drawSprite(int out_x, int out_y, int spriteWidth, int spriteHeight, int spriteBytesPerPixel, const unsigned char* spriteData);
//<<<<<<< Updated upstream
void printNum(int row,int column,int num);
void printCoins();
void printLives();
//=======
void drawOneObject(Object* obj);
void drawObjectMap(Object* map);
void updateObjectMap(Object* map);
//>>>>>>> Stashed changes
void drawEndGame();
void startValues();

#endif /* RENDER_H_ */
