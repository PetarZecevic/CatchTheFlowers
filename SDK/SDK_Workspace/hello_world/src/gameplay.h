#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "bunny.h"
#include "object.h"


void printNum(int row,int column,int num);
void printCoins();
// Init graphics.
void init();
void initObjectMap(Object* map);
// Get user input and update bunnies transit direction.
void updateBunnies(Bunny bunnies[]);
char getPressedKey();
// Insert flower or trash on map.
void insertObjects(Object* map);
void updateObjectRotations(Object* map);
void clearObjectPaths(Object* map);
// Iterate through object and check for collision.
// If collision happens, check bunny state, to determine if bunny is hurt.
void checkCollisions(Object* map, Bunny bunnies[]);
void gameLoop();

#endif /* GAMEPLAY_H_ */
