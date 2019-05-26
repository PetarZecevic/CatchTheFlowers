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
#include <stdlib.h>     /* srand, rand */
#include "vga_periph_mem.h"
#include "xparameters.h"
#include "gameplay.h"
#include "game_config.h"
#include "bunny.h"
#include "sprite.h"

GameStats gameStats;
unsigned char map1[SIZEROW][SIZECOLUMN] = {{[0 ... SIZEROW-1] = GRASS}, {[0 ... SIZECOLUMN-1] = GRASS}};
unsigned char box[3] = {DIRT, DIRT, DIRT}; // Boxes that collect flowers, DIRT-means collect, BUSH-means reject.
int itemColumns[3] = {2, 10, 17}; // Columns on map from which items will appear.
bool endGame = false;


/*
//extracting pixel data from a picture for printing out on the display
void drawSprite(int in_x, int in_y, int out_x, int out_y, int width, int height)
{
	int x, y, ox, oy, oi, iy, ix, ii, R, G, B, RGB;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			ox = out_x + x;
			oy = out_y + y;
			oi = oy * 320 + ox;
			ix = in_x + x;
			iy = in_y + y;
			ii = iy * towerdefence_sprites.width + ix;
			R = towerdefence_sprites.pixel_data[ii
					* towerdefence_sprites.bytes_per_pixel] >> 5;
			G = towerdefence_sprites.pixel_data[ii
					* towerdefence_sprites.bytes_per_pixel + 1] >> 5;
			B = towerdefence_sprites.pixel_data[ii
					* towerdefence_sprites.bytes_per_pixel + 2] >> 5;
			R <<= 6;
			G <<= 3;
			RGB = R | G | B;

			VGA_PERIPH_MEM_mWriteMemory(
					XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + GRAPHICS_MEM_OFF
							+ oi * 4 , RGB);
		}
	}
}
*/

void drawMap()
{
	int row, column;
	for (row = 0; row < SIZEROW; row++)
	{
		for (column = 0; column < SIZECOLUMN; column++)
		{
			if(mapChanges[row][column])
			{
				mapChanges[row][column] = false;
				if (map1[row][column] == GRASS)
					drawSprite(16, 0, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == DIRT || map1[row][column] == DIRTPREVIOUS)
					drawSprite(0, 0, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == BUSH)
					drawSprite(32, 0, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == CREEP)
					drawSprite(48, 0, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == CREEP1)
					drawSprite(48, 16, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == CREEP2)
					drawSprite(48, 32, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == CREEP3)
					drawSprite(48, 48, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == CREEP4)
					drawSprite(48, 64, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == LAKE1)
					drawSprite(0, 16, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == LAKE2)
					drawSprite(16, 16, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == LAKE3)
					drawSprite(32, 16, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == LAKE4)
					drawSprite(0, 32, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == LAKE5)
					drawSprite(16, 32, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == LAKE6)
					drawSprite(32, 32, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == SPOT)
					drawSprite(64, 0, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == SELECTEDSPOT)
					drawSprite(64, 16, column * 16, row * 16, 16, 16);

				else if (map1[row][column] == TOWER)
					drawSprite(64,32,column*16,row*16,16,16);

				else if (map1[row][column] == TOWER2)
					drawSprite(80,32,column*16,row*16,16,16);

				else if(map1[row][column] == SELECTEDTOWER)
					drawSprite(64,48,column*16,row*16,16,16);

				else if(map1[row][column] == SELECTEDTOWER2)
					drawSprite(80,48,column*16,row*16,16,16);

				else if(map1[row][column] == HP1)
					drawSprite(112,0,column*16,row*16,16,16);

				else if(map1[row][column] == HP2)
					drawSprite(112,16,column*16,row*16,16,16);

				else if(map1[row][column] == HP3)
					drawSprite(112,32,column*16,row*16,16,16);

				else if(map1[row][column] == HP4)
					drawSprite(112,48,column*16,row*16,16,16);
			}
		}
	}
}

//draw amount of coins
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
}

//max coins 99, calls printNum for drawing left or right coin
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
}

//Make items fall.
void moveItems()
{
	int i,j;
	unsigned char temp;
	for(i = 0; i < 3; i++)
	{
		j = SIZEROW-2;

		// Check for final condition.
		temp = map1[j][itemColumns[i]];
		if(temp == CREEP)
		{
			if(box[i] == DIRT) // flower
				gameStats.coinsCollected += 1;
			else if(box[i] == BUSH)
				gameStats.healthPoints--;
		}
		else if(temp == CREEP4) // rock
		{
			if(box[i] == DIRT)
				gameStats.healthPoints--;
		}
		map1[j][itemColumns[i]] = GRASS;
		mapChanges[j][itemColumns[i]] = true;

		for(j--; j >= 0; j--)
		{
			if(map1[j][itemColumns[i]] == CREEP || map1[j][itemColumns[i]] == CREEP4)
			{
				temp = map1[j][itemColumns[i]];
				map1[j][itemColumns[i]] = GRASS;
				map1[j+1][itemColumns[i]] = temp;
				mapChanges[j][itemColumns[i]] = true;
				mapChanges[j+1][itemColumns[i]] = true;
			}
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
		pressedKey = 'R';
	else if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & SW0) == 0)
		pressedKey = '0';
	else if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & SW1) == 0)
		pressedKey = '1';
	else
		pressedKey = 'n';

	return pressedKey;
}

// Insert item into map, in first row and predetermined column.
// Maximum three items can be inserted at once.
void insertItems()
{
	int insertItem; // stores random number that determines whether item will be inserted into column.
	int flowerOrRock; // stores random number that determines which item will be inserted.

	int i;
	for(i = 0; i < 3; i++)
	{
		insertItem = rand() % 2;
		if(insertItem == 1)
		{
			flowerOrRock = rand() % 2; // equal probability.
			if(flowerOrRock == 1)
				map1[0][itemColumns[i]] = CREEP; // insert flower.
			else
				map1[0][itemColumns[i]] = CREEP4; // insert rock.
			mapChanges[0][itemColumns[i]] = true;
		}
	}
}

void drawEndGame()
{
	int row,column;
	while(1)
	{
		for (row = 0; row < SIZEROW; row++)
		{
			for (column = 0; column < SIZECOLUMN; column++)
			{
				if (gameOver[row][column] == DIRT)
					drawSprite(0, 0, column * 16, row * 16, 16, 16);
				else if (gameOver[row][column] == CREEP)
				{
					drawSprite(48, 0, column * 16, row * 16, 16, 16);
					gameOver[row][column] = CREEP4;
				}
				else if (gameOver[row][column] == CREEP4)
				{
					drawSprite(48, 64, column * 16, row * 16, 16, 16);
					gameOver[row][column] = CREEP;
				}
			}
		}
	}
}

// Get input from user, and check whether to change type of boxes.
void updateBoxes(){
	// Change box type.
	int dummy;
	char pressedKey;
	for(dummy = 0; dummy < 1000; dummy++)
	{
		pressedKey = getPressedKey();
		if(pressedKey != 'n')
		{
			if(pressedKey == 'r')
			{
				if(box[2] == DIRT)
					box[2] = BUSH;
				else
					box[2] = DIRT;

				map1[SIZEROW-1][17] = box[2];
				mapChanges[SIZEROW-1][17] = true;
			}
			else if(pressedKey == 'l')
			{
				if(box[0] == DIRT)
					box[0] = BUSH;
				else
					box[0] = DIRT;

				map1[SIZEROW-1][2] = box[0];
				mapChanges[SIZEROW-1][2] = true;
			}
			else if(pressedKey == 'R')
			{
				if(box[1] == DIRT)
					box[1] = BUSH;
				else
					box[1] = DIRT;

				map1[SIZEROW-1][10] = box[1];
				mapChanges[SIZEROW-1][10] = true;
			}
			break;
		}
	}
}

// First level gameplay, user plays until he loses all health points.
void gameLoop()
{
	// Load first map background.
	int row,column;
	for (row = 0; row < SIZEROW; row++)
	{
		for (column = 0; column < SIZECOLUMN; column++)
		{
			map1[row][column] = map1Origin[row][column];
			mapChanges[row][column] = true;
		}
	}

	// Game parameters.
	unsigned int userInputSpeed=0;
	unsigned int itemSpeed = 0;
	int insertItemTime = 0;

	// Reset global variables.
	gameStats.healthPoints = 3;
	gameStats.coinsCollected = 0;
	endGame = false;

	// Initialize map.
	drawMap();

	printCoins();
	printLives();

	drawSprite(8,64,16,0,8,8);
	drawSprite(8,72,16,8,8,8);

	// Start game loop.
	while(1)
	{
		if(endGame || gameStats.healthPoints == 0)
		{
			break;
		}

		if (userInputSpeed == 10000)
		{
			updateBoxes();
			userInputSpeed = 0;
		}

		if (itemSpeed == 1000000)
		{
			if(insertItemTime == 5)
			{
				insertItems();
				insertItemTime = 0;
			}

			moveItems();
			printCoins();
			printLives();
			drawMap();

			insertItemTime++;
			itemSpeed=0;
		}

		itemSpeed++;
		userInputSpeed++;
	}
}
