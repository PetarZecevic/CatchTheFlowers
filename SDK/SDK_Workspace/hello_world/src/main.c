#include "gameplay.h"
#include <time.h>
#include <stdlib.h>
#include "platform.h"

#define ITEM_STEP 2

extern const BackgroundSprite ground, sky;
extern const BackgroundSprite rose_flower_1, rose_flower_2, yellow_flower_1, yellow_flower_2, trash;

Bunny bunnies[3];

typedef struct{
	int row;
	int col;
	bool isFlower;//true-flower,false-garbage
	bool roseOrYellow; //true-pink,false-yellow
	bool position;
}Object;

Object leftCol[10];
Object centreCol[10];
Object rightCol[10];

void setColumn(){
	int i;
	for(i=0;i<10;i++){
		leftCol[i].col=3;
		centreCol[i].col=10;
		rightCol[i].col=16;
	}
	for(i=0;i<10;i++){
		leftCol[i].row=0;
		centreCol[i].row=0;
		rightCol[i].row=0;
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
	}

}

/** @param dir is used to determine if flower needs to rotate.
*/
void drawObject(int row, int column, bool dir, bool roseOrYellow,bool isFlower)
{

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

/*int random(int min_number,int max_number){
	int value;
	value=rand() % (max_number + 1 - min_number) + min_number;
	return value;
}*/

void insertObjects()
{
	//TODO: Insert flower or trash in map, determine in which way to insert it.

	return;
}



void updateObjects()
{
	//TODO: Update object position.
	// Move them by FLOWER_STEP rows using drawFlower function.
	int i;
	for(i=0;i<10;i++){
		leftCol[i].row+=ITEM_STEP;
		centreCol[i].row+=ITEM_STEP;
		rightCol[i].row+=ITEM_STEP;
		drawObject(leftCol[i].row, leftCol[i].col, leftCol[i].position, leftCol[i].roseOrYellow,leftCol[i].isFlower);
		drawObject(centreCol[i].row, centreCol[i].col, centreCol[i].position, centreCol[i].roseOrYellow,centreCol[i].isFlower);
		drawObject(rightCol[i].row, rightCol[i].col, rightCol[i].position, rightCol[i].roseOrYellow,rightCol[i].isFlower);

	}

	return;
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

	static const int ANIMATION_SPEED = 80000;
	static const int ITEM_SPEED = 20000;
	static const int ROTATION_SPEED = 50000;
	static const int INSERT_SPEED = 80000;


	//static int row1 = 0, row2 = 0;
	/*
	 struct Object{
	 	 int row;
	 	 int column;
	 	 bool isFlower;
	 	 bool roseOrYellow;
	 	 bool position;
	 };
	 */
	static bool dir1 = true, dir2 = true;

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
			updateObjects();
			itemMovingSpeed = 0;
		}

		if(itemRotationSpeed == ROTATION_SPEED)
		{
			dir1 = !dir1;
			dir2 = !dir2;
			itemRotationSpeed = 0;
		}

		itemMovingSpeed++;
		itemRotationSpeed++;
		itemInsertSpeed++;
		bunnyMovingSpeed++;
	}
}

int main()
{
	srand(time(NULL));
	cleanup_platform();

	init_platform();
	init();

	//gameLoop();
	//drawEndGame();

	test();
	return 0;
}
