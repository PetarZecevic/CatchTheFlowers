#include "gameplay.h"
#include "platform.h"
#include "stdlib.h"

#define ITEM_STEP 3

extern const BackgroundSprite ground, sky;
extern const BackgroundSprite rose_flower_1, rose_flower_2, yellow_flower_1, yellow_flower_2, trash;

Bunny bunnies[3];

typedef struct{
	int row;
	int col;
	bool isFlower;//true-flower,false-garbage
	bool roseOrYellow; //true-pink,false-yellow
	bool position;
	bool valid; //true-draw it, false-do not draw it
}Object;

Object mapObject[3][10];

const int ANIMATION_SPEED = 80000, ITEM_SPEED = 50000, ROTATION_SPEED = 50000, INSERT_SPEED = 600000, TRAIL_LENGTH = 4;

void setColumn()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<10;j++)
		{
			mapObject[i][j].row=0;
			mapObject[i][j].valid=false;
			mapObject[i][j].isFlower=false;
			if(i==0)
			{
				mapObject[i][j].col=3;
			}
			else if(i==1)
			{
				mapObject[i][j].col=10;
			}
			else
			{
				mapObject[i][j].col=16;
			}
		}
	}
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

// Get user input and update bunnies transit direction.
void updateBunnies()
{
	//static int dummy;
	static char pressedKey;

	pressedKey = getPressedKey();
	if(pressedKey != 'n')
	{
		if(pressedKey == 'r')
		{
			// Right bunny update.
			flipBunnyBasket(&bunnies[2]);
		}
		else if(pressedKey == 'l')
		{
			// Center bunny update.
			flipBunnyBasket(&bunnies[0]);
		}
		else if(pressedKey == 'c')
		{
			// Left bunny update.
			flipBunnyBasket(&bunnies[1]);
		}
		// Added test case for HURT state.
		else if(pressedKey == 'u')
		{
			bunnies[0].state = HURT;
		}
	}

}

/** @param dir is used to determine if flower needs to rotate.
*/
void drawOneObject(int row, int column, bool dir, bool roseOrYellow,bool isFlower)
{
	column *= 16;

	if(isFlower){
		if(dir)
		{
			if(roseOrYellow)
			{
				drawSprite(column, row, 16, 16, 3, rose_flower_1.pixel_data);
			}
			else
			{
				drawSprite(column, row, 16, 16, 3, yellow_flower_1.pixel_data);
			}
		}
		else
		{
			if(roseOrYellow)
			{
				drawSprite(column, row, 16, 16, 3, rose_flower_2.pixel_data);
			}
			else
			{
				drawSprite(column, row, 16, 16, 3, yellow_flower_2.pixel_data);
			}
		}
	}
	else
	{
		drawSprite(column, row, 16, 16, 3, trash.pixel_data);
	}
}

void insertObjects()
{
	//TODO: Insert flower or trash in map, determine in which way to insert it.
	int column = rand() % 3;
	int flowerOrRock = rand() % 10;

	for(int i = 0; i < 10; i++)
	{
		if(!mapObject[column][i].valid)
		{
			mapObject[column][i].row = 0;
			if(flowerOrRock > 7)
			{
				mapObject[column][i].isFlower = false;
			}
			else
			{
				mapObject[column][i].isFlower = true;
				int roseOrYellow = rand() % 2;
				if(roseOrYellow == 0)
				{
					mapObject[column][i].roseOrYellow = true;
				}
				else
				{
					mapObject[column][i].roseOrYellow = false;
				}
			}
			mapObject[column][i].position = true;
			mapObject[column][i].valid = true;
			break;
		}
	}
}


void drawObjects()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<10;j++)
		{
			if(mapObject[i][j].valid==true)
			{
				drawOneObject(mapObject[i][j].row, mapObject[i][j].col,mapObject[i][j].position,mapObject[i][j].roseOrYellow,mapObject[i][j].isFlower);
			}
		}
	}
}


void updateObjects()
{
	//TODO: Update object position.
	// Move them by FLOWER_STEP rows using drawFlower function.
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<10;j++)
		{
			if(mapObject[i][j].valid)
			{
				mapObject[i][j].row += ITEM_STEP;
			}
		}

	}
}

void updateObjectRotations()
{
	int i, j;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 10; j++)
		{
			if(mapObject[i][j].valid)
			{
				if(mapObject[i][j].isFlower)
				{
					mapObject[i][j].position = !mapObject[i][j].position;
				}
			}
		}
	}
}

void clearObjectPaths()
{
	int row;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(mapObject[i][j].valid)
			{
				row = mapObject[i][j].row;
				if(row >= TRAIL_LENGTH*ITEM_STEP)
				{
					drawSprite(mapObject[i][j].col*16, row - TRAIL_LENGTH*ITEM_STEP, 16, TRAIL_LENGTH*ITEM_STEP, 3, sky.pixel_data);
				}
			}
		}
	}
}

// Iterate through object and check for collision.
// If collision happens, check bunny state, to determine if bunny is hurt.
void checkCollisions()
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(mapObject[i][j].valid)
			{
				if(mapObject[i][j].row >= 144)
				{
					mapObject[i][j].valid = false;
					// Check if bunny is hurt.
					if(bunnies[i].state != DOWN && !mapObject[i][j].isFlower)
					{
						bunnies[i].state = HURT;
					}
					drawBackgroundSprite(9, mapObject[i][j].col, sky);
				}
			}
		}
	}
}

void test()
{

	Bunny_Init(&bunnies[0], 10, 2);
	Bunny_Init(&bunnies[1], 10, 9);
	Bunny_Init(&bunnies[2], 10, 15);

	static int bunnyMovingSpeed = 0;
	static int itemMovingSpeed = 0;
	static int itemRotationSpeed = 0;
	static int itemInsertSpeed = 0;

	// Draw background.
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 20; j++){
			if(i < 13)
			{
				drawBackgroundSprite(i, j, sky);
			}
			else
			{
				drawBackgroundSprite(i, j, ground);
			}
		}
	}

	/*
	setColumn();

	// Simulate game loop.
	while(1)
	{
		updateBunnies();

		if(bunnyMovingSpeed == ANIMATION_SPEED)
		{
			for(int j = 0; j < 3; j++)
			{
				drawBunny(&bunnies[j]);
				Bunny_ChangeFrame(&bunnies[j]);
			}
			bunnyMovingSpeed = 0;
		}

		if(itemInsertSpeed == INSERT_SPEED)
		{
			insertObjects();
			itemInsertSpeed = 0;
		}

		if(itemMovingSpeed == ITEM_SPEED){

			clearObjectPaths();
			drawObjects();
			checkCollisions();
			updateObjects();
			itemMovingSpeed = 0;
		}

		if(itemRotationSpeed == ROTATION_SPEED)
		{
			updateObjectRotations();
			itemRotationSpeed = 0;
		}

		itemMovingSpeed++;
		itemRotationSpeed++;
		itemInsertSpeed++;
		bunnyMovingSpeed++;
	}
	*/
}

int main()
{
	cleanup_platform();

	init_platform();
	init();

	//gameLoop();
	//drawEndGame();

	test();
	return 0;
}
