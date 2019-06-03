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
	bool valid; //true-draw it, false-do not draw it
}Object;



Object mapObject[3][10];

void setColumn(){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<10;j++){
			mapObject[i][j].row=0;
			mapObject[i][j].valid=true;
			mapObject[i][j].isFlower=false;
			if(i==0){
				mapObject[i][j].col=3;
			}
			else if(i==1){
				mapObject[i][j].col=10;
			}
			else{
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
void drawObject(int row, int column, bool dir, bool roseOrYellow,bool isFlower)
{
	row *= 16;
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
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<10;j++){
			mapObject[i][j].row+=ITEM_STEP;
			if(mapObject[i][j].row<160){
				drawObject(mapObject[i][j].row, mapObject[i][j].col,mapObject[i][j].position,mapObject[i][j].roseOrYellow,mapObject[i][j].isFlower);
			}
			else{
				mapObject[i][j].valid=false;
			}
		}

	}

	return;
}

// Iterate through object and check for collision.
// If collision happens, check bunny state, to determine if bunny is hurt.
void checkCollisions()
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(mapObject[i][j].row >= 160)
			{
				// Check if bunny is hurt.
				if(bunnies[i].state != DOWN && !mapObject[i][j].isFlower)
				{
					bunnies[i].state = HURT;
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

	static const int ANIMATION_SPEED = 80000;
	static const int ITEM_SPEED = 20000;
	static const int ROTATION_SPEED = 50000;
	static const int INSERT_SPEED = 80000;


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
			checkCollisions();
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
