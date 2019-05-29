#ifndef BUNNY_H_
#define BUNNY_H_

#include <stdbool.h>

typedef enum {UP, TRANSIT, DOWN} BunnyStates;
typedef enum {LEFT2 = -2, LEFT1, CENTER, RIGHT1, RIGHT2, TRANSIT1, TRANSIT2, DOWN1} BunnyFrames;
typedef enum {MOV_LEFT = -1, MOV_RIGHT = 1} BunnyMovingDirection;
typedef enum {TRANSIT_UP, TRANSIT_DOWN, NONE} BunnyTransitDirection;

typedef struct{
	BunnyStates state; // Indicator for gameplay.
	BunnyFrames frame; // Indicator for frame which will be draw on the screen.
	BunnyMovingDirection movingDir; // moving to left or to Right.
	BunnyTransitDirection transitDir; // going from basket up to basket down or reverse.
	int column; // starting column from which bunny appears on the screen.
	int row; // starting row from which bunny appears on the screen.
}Bunny;


void Bunny_Init(Bunny* bunny, int row, int column);
// Automatically change frames based on state and directions.
void Bunny_ChangeFrame(Bunny* bunny);

#endif /* BUNNY_H_ */
