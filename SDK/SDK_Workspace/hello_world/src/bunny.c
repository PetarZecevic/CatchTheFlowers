#include "bunny.h"

void Bunny_Init(Bunny bunny, unsigned int row, unsigned int column)
{
	bunny.state = UP;
	bunny.frame = CENTER;
	bunny.movingDir = MOV_LEFT;
	bunny.transitDir = NONE;
	bunny.row = row;
	bunny.column = column;
}

void Bunny_ChangeFrame(Bunny bunny)
{
	switch(bunny.state)
	{
	case UP:
		if(bunny.transitDir == TRANSIT_DOWN)
		{
			// Start transition animation.
			bunny.state = TRANSIT;
			bunny.frame = TRANSIT1;
		}
		// If no transition happens continue moving animation.
		else
		{
			if(bunny.frame == LEFT2)
				bunny.movingDir = MOV_RIGHT;
			else if(bunny.frame == RIGHT2)
				bunny.movingDir = MOV_LEFT;
			bunny.frame += bunny.movingDir;
		}
		break;

	case TRANSIT:
		if(bunny.transitDir == TRANSIT_DOWN)
		{
			bunny.frame++;
			if(bunny.frame == DOWN1)
			{
				// Finished transition.
				bunny.state = DOWN;
				bunny.transitDir = NONE;
			}
		}
		else if(bunny.transitDir == TRANSIT_UP)
		{
			bunny.frame--;
			if(bunny.frame == RIGHT2)
			{
				// Finished transition, return to central position and start moving to left.
				bunny.state = UP;
				bunny.frame = CENTER;
				bunny.movingDir = MOV_LEFT;
				bunny.transitDir = NONE;
			}
		}
		break;

	case DOWN:
		if(bunny.transitDir == TRANSIT_UP)
		{
			// Start transition animation.
			bunny.state = TRANSIT;
			bunny.frame = TRANSIT2;

		}
		break;
	default:
		break;
	}
}



