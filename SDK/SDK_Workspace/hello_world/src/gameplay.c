/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>

#include "xio.h"
#include "xil_exception.h"
#include "stdlib.h"     /* srand, rand */
#include "vga_periph_mem.h"
#include "xparameters.h"
#include "gameplay.h"
#include "controls.h"
//#include "game_config.h"
#include "bunny.h"
#include "sprite.h"
#include "render.h"

#define ITEM_STEP 3
#define SIZEROW 15
#define SIZECOLUMN 20

typedef struct{
	int healthPoints;
	int coinsCollected;
}GameStats;


extern const BackgroundSprite ground, sky,rose_flower_1, yellow_flower_1;
extern const ItemSprite life;


GameStats gameStats;
Object matrix[PATHS][MAX_OBJECTS];

const int bunnyColumns[3] = {2, 8, 14};

const int ANIMATION_SPEED = 80000, ITEM_SPEED = 50000, ROTATION_SPEED = 50000, INSERT_SPEED = 600000, TRAIL_LENGTH = 4;

//draw amount of coins
/*
void printNum(int row,int column,int num)
{

	if(num==0)
		drawSprite(16,48,column,row,8,8);

	else if(num==1)
		drawSprite(24,48,column,row,8,8);

	else if(num==2)
		drawSprite(32,48,column,row,8,8);

	else if(num==3)
		drawSprite(40,48,column,row,8,8);

	else if(num==4)
		drawSprite(16,56,column,row,8,8);

	else if(num==5)
		drawSprite(24,56,column,row,8,8);

	else if(num==6)
		drawSprite(32,56,column,row,8,8);

	else if(num==7)
		drawSprite(40,56,column,row,8,8);

	else if(num==8)
		drawSprite(16,64,column,row,8,8);

	if(num==9)
		drawSprite(24,64,column,row,8,8);
}*/

//max coins 99, calls printNum for drawing left or right coin
/*
void printCoins()
{
	int l,r;
	l = gameStats.coinsCollected / 10;
	r = gameStats.coinsCollected % 10;
	printNum(0,8,r);

	if(l!=0)
		printNum(0,0,l);
	else
		drawSprite(16,0,0,0,8,8);
}

//printing the number of lives left
void printLives(){
	int l,r;
	l = gameStats.healthPoints / 10;
	r = gameStats.healthPoints % 10;
	printNum(8,8,r);

	if(l!=0)
		printNum(8,0,l);
	else
		drawSprite(16,0,0,8,8,8);
}*/

void initObjectMap(Object* map)
{
	int i,j;
	for(i = 0; i < PATHS; i++)
	{
		for(j = 0; j < MAX_OBJECTS; j++)
		{
			map[i*MAX_OBJECTS + j].row = 0;
			map[i*MAX_OBJECTS + j].valid = false;
			map[i*MAX_OBJECTS + j].isFlower = false;
			map[i*MAX_OBJECTS + j].column = bunnyColumns[i] + 1;
		}
	}
}



void updateObjectMap(Object* map)
{
	int i,j;
	for(i = 0; i < PATHS; i++)
	{
		for(j = 0; j < MAX_OBJECTS; j++)
		{
			if(map[i * MAX_OBJECTS + j].valid)
			{
				map[i * MAX_OBJECTS + j].row += ITEM_STEP;
			}
		}
	}
}

// Get user input and update bunnies transit direction.
void updateBunnies(Bunny bunnies[])
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
			//bunnies[0].state = HURT;
			drawEndGame();
		}
	}

}

char getPressedKey()
{
	char pressedKey;

	if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & RIGHT) == 0)
		pressedKey = 'r';
	else if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & LEFT) == 0)
		pressedKey = 'l';
	else if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & UP) == 0)
		pressedKey = 'u';
	else if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & CENTER) == 0)
		pressedKey = 'c';
	else if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & SW0) == 0)
		pressedKey = '0';
	else if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & SW1) == 0)
		pressedKey = '1';
	else
		pressedKey = 'n';

	return pressedKey;
}


// Insert flower or trash on map.
void insertObjects(Object* map)
{
	int path = rand() % 3;
	int flowerOrRock = rand() % 10;

	for(int i = 0; i < MAX_OBJECTS; i++)
	{
		if(!map[path * MAX_OBJECTS + i].valid) // bug was here.
		{
			map[path * MAX_OBJECTS + i].row = 0;
			if(flowerOrRock > 7)
			{
				map[path * MAX_OBJECTS + i].isFlower = false;
			}
			else
			{
				map[path * MAX_OBJECTS + i].isFlower = true;
				int roseOrYellow = rand() % 2;
				if(roseOrYellow == 0)
				{
					map[path * MAX_OBJECTS + i].roseOrYellow = true;
				}
				else
				{
					map[path * MAX_OBJECTS + i].roseOrYellow = false;
				}
			}
			map[path * MAX_OBJECTS + i].position = true;
			map[path * MAX_OBJECTS + i].valid = true;
			break;
		}
	}
}

void updateObjectRotations(Object* map)
{
	int i, j;
	for(i = 0; i < PATHS; i++)
	{
		for(j = 0; j < MAX_OBJECTS; j++)
		{
			if(map[i * MAX_OBJECTS + j].valid)
			{
				if(map[i * MAX_OBJECTS + j].isFlower)
				{
					map[i * MAX_OBJECTS + j].position = !(map[i * MAX_OBJECTS + j].position);
				}
			}
		}
	}
}

void clearObjectPaths(Object* map)
{
	int row, column;
	for(int i = 0; i < PATHS; i++)
	{
		for(int j = 0; j < MAX_OBJECTS; j++)
		{
			if(map[i*MAX_OBJECTS + j].valid)
			{
				row = map[i*MAX_OBJECTS + j].row;
				column = map[i*MAX_OBJECTS + j].column * 16;
				if(row >= TRAIL_LENGTH*ITEM_STEP)
				{
					drawSprite(column, row - TRAIL_LENGTH * ITEM_STEP, 16, TRAIL_LENGTH * ITEM_STEP, 3, sky.pixel_data);
				}
				if(row < 4 && row >= 1){
					drawSprite(column, 1, 16, row-1, 3, sky.pixel_data);
				}
			}
		}
	}
}

// Iterate through object and check for collision.
// If collision happens, check bunny state, to determine if bunny is hurt.
void checkCollisions(Object* map, Bunny bunnies[])
{
	for(int i = 0; i < PATHS; i++)
	{
		for(int j = 0; j < MAX_OBJECTS; j++)
		{
			if(map[i * MAX_OBJECTS + j].valid)
			{
				if(map[i * MAX_OBJECTS + j].row >= 144)
				{
					map[i * MAX_OBJECTS + j].valid = false;
					// Check if bunny is hurt.
					if(bunnies[i].state != DOWN && !(map[i * MAX_OBJECTS + j].isFlower))
					{
						bunnies[i].state = HURT;
						gameStats.healthPoints--;
						printLives(gameStats);
					}
					drawBackgroundSprite(9, map[i * MAX_OBJECTS + j].column, sky);
				}
			}
		}
	}
}

void gameLoop()
{

	Bunny bunnies[3];

	initObjectMap((Object*) matrix);

	for(int i = 0; i < 3; i++)
	{
		Bunny_Init(&bunnies[i], 10, bunnyColumns[i]);
	}

	static int bunnyMovingSpeed = 0;
	static int itemMovingSpeed = 0;
	static int itemRotationSpeed = 0;
	static int itemInsertSpeed = 0;

	// Draw background.
	for(int i = 0; i < SIZEROW; i++)
	{
		for(int j = 0; j < SIZECOLUMN; j++)
		{
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



	gameStats.coinsCollected=0;
	gameStats.healthPoints=9;


	startValues();

	// Simulate game loop.
	while(1)
	{
		updateBunnies(bunnies);

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
			insertObjects((Object*) matrix);
			itemInsertSpeed = 0;
		}

		if(itemMovingSpeed == ITEM_SPEED){

			clearObjectPaths((Object*) matrix);
			drawObjectMap((Object*) matrix);
			checkCollisions((Object*) matrix, bunnies);
			updateObjectMap((Object*) matrix);
			itemMovingSpeed = 0;
		}

		if(itemRotationSpeed == ROTATION_SPEED)
		{
			updateObjectRotations((Object*) matrix);
			itemRotationSpeed = 0;
		}

		itemMovingSpeed++;
		itemRotationSpeed++;
		itemInsertSpeed++;
		bunnyMovingSpeed++;
	}
}

