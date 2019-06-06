#include "bunny.h"

void Bunny_Init(Bunny* bunny, int row, int column)
{
	bunny->state = UP;
	bunny->frame = CENTER1;
	bunny->movingDir = MOV_LEFT;
	bunny->transitDir = NONE;
	bunny->row = row;
	bunny->column = column;
}

void flipBunnyBasket(Bunny* bunny)
{
	if(bunny->state == UP)
	{
		bunny->transitDir = TRANSIT_DOWN;
	}
	else if(bunny->state == DOWN)
	{
		bunny->transitDir = TRANSIT_UP;
	}
}

void Bunny_ChangeFrame(Bunny* bunny)
{
	switch(bunny->state)
	{
	case UP:
		if(bunny->transitDir == TRANSIT_DOWN)
		{
			// Start transition animation.
			bunny->state = TRANSIT;
			bunny->frame = TRANSIT1;
		}
		// If no transition happens continue moving animation.
		else
		{
			if(bunny->frame == LEFT2)
				bunny->movingDir = MOV_RIGHT;
			else if(bunny->frame == RIGHT2)
				bunny->movingDir = MOV_LEFT;
			bunny->frame += bunny->movingDir;
		}
		break;

	case TRANSIT:
		if(bunny->transitDir == TRANSIT_DOWN)
		{
			// Finished transition.
			bunny->state = DOWN;
			bunny->frame = DOWN1;
			bunny->transitDir = NONE;
		}
		else if(bunny->transitDir == TRANSIT_UP)
		{
			// Finished transition, return to central position and start moving to left.
			bunny->state = UP;
			bunny->frame = CENTER1;
			bunny->movingDir = MOV_LEFT;
			bunny->transitDir = NONE;
		}
		break;
	case HURT:
		bunny->transitDir = NONE;
		if(bunny->frame == HURT1)
		{
			bunny->frame = CENTER1;
			bunny->state = UP;
		}
		else
			bunny->frame = HURT1;
		break;
	case DOWN:
		if(bunny->transitDir == TRANSIT_UP)
		{
			// Start transition animation.
			bunny->state = TRANSIT;
			bunny->frame = TRANSIT1;

		}
		break;
	default:
		break;
	}
}



