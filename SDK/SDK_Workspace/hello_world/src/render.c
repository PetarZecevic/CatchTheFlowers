#include "render.h"



#include "vga_periph_mem.h"
#include "xparameters.h"
//<<<<<<< Updated upstream
#include "game_config.h"
//=======
#include "object.h"

extern const BunnySprite bunny_left_1, bunny_left_2, bunny_right_1, bunny_right_2,
	bunny_stable, bunny_transit_1, bunny_down_1,bunny_hurt;

extern const BackgroundSprite rose_flower_1, rose_flower_2, yellow_flower_1, yellow_flower_2, trash, trash_broke, sky;

extern const ItemSprite zero,one,two,three,four,five,six,seven,eight,nine,life;


void drawSprite(int out_x, int out_y, int spriteWidth, int spriteHeight, int spriteBytesPerPixel, const unsigned char* spriteData)
{
	static int x, y, ox, oy, oi, ii, R, G, B, RGB;
	for (y = 0; y < spriteHeight; y++)
	{
		for (x = 0; x < spriteWidth; x++)
		{
			ox = out_x + x;
			oy = out_y + y;
			oi = oy * 320 + ox;
			ii = y * spriteWidth + x;
			
			R = spriteData[ii*spriteBytesPerPixel] >> 5;
			G = spriteData[ii*spriteBytesPerPixel + 1] >> 5;
			B = spriteData[ii*spriteBytesPerPixel + 2] >> 5;

			R <<= 6;
			G <<= 3;

			RGB = R | G | B;

			VGA_PERIPH_MEM_mWriteMemory(
					XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + GRAPHICS_MEM_OFF
							+ oi * 4 , RGB);
		}
	}
}

void drawBackgroundSprite(unsigned int row, unsigned int column, const BackgroundSprite background)
{
	static int offset_y, offset_x;
	offset_y = row*16;
	offset_x = column*16;
	drawSprite(offset_x, offset_y, background.width, background.height, background.bytes_per_pixel, background.pixel_data);
}


void drawBunny(Bunny* bunny)
{
	static int row, col;
	row = bunny->row * 16;
	col = bunny->column * 16;

	switch(bunny->frame)
	{
	case LEFT2:
		drawSprite(col, row, 48, 80, bunny_left_2.bytes_per_pixel, bunny_left_2.pixel_data);
		break;
	case LEFT1:
		drawSprite(col, row, 48, 80, bunny_left_1.bytes_per_pixel, bunny_left_1.pixel_data);
		break;
	case CENTER1:
		drawSprite(col, row, 48, 80, bunny_stable.bytes_per_pixel, bunny_stable.pixel_data);
		break;
	case RIGHT1:
		drawSprite(col, row, 48, 80, bunny_right_1.bytes_per_pixel, bunny_right_1.pixel_data);
		break;
	case RIGHT2:
		drawSprite(col, row, 48, 80, bunny_right_2.bytes_per_pixel, bunny_right_2.pixel_data);
		break;
	case TRANSIT1:
		drawSprite(col, row, 48, 80, bunny_transit_1.bytes_per_pixel, bunny_transit_1.pixel_data);
		break;
	case DOWN1:
		drawSprite(col, row, 48, 80, bunny_down_1.bytes_per_pixel, bunny_down_1.pixel_data);
		break;
	case HURT1:
		drawSprite(col, row, 48, 80, bunny_hurt.bytes_per_pixel, bunny_hurt.pixel_data);
		break;
	default:
		break;
	}
}

void printNum(int row,int column,int num)
{

	row=row*16;
	column=column*16;
	if(num==0)
		drawSprite(column, row, 16, 16, zero.bytes_per_pixel,zero.pixel_data);
	else if(num==1)
		drawSprite(column, row, 16, 16, one.bytes_per_pixel,one.pixel_data);
	else if(num==2)
		drawSprite(column, row, 16, 16, two.bytes_per_pixel,two.pixel_data);
	else if(num==3)
		drawSprite(column, row, 16, 16, three.bytes_per_pixel,three.pixel_data);
	else if(num==4)
		drawSprite(column, row, 16, 16, four.bytes_per_pixel,four.pixel_data);
	else if(num==5)
		drawSprite(column, row, 16, 16, five.bytes_per_pixel,five.pixel_data);
	else if(num==6)
		drawSprite(column, row, 16, 16, six.bytes_per_pixel,six.pixel_data);
	else if(num==7)
		drawSprite(column, row, 16, 16,seven.bytes_per_pixel,seven.pixel_data);
	else if(num==8)
		drawSprite(column, row, 16, 16, eight.bytes_per_pixel,eight.pixel_data);
	if(num==9)
		drawSprite(column, row, 16, 16, nine.bytes_per_pixel,nine.pixel_data);
}

void printCoins(GameStats gameStats)
{
	int l,r;
	l = gameStats.coinsCollected / 10;
	r = gameStats.coinsCollected % 10;
	printNum(1,19,r);

	if(l!=0)
		printNum(1,18,l);
	/*else
		drawSprite(16,0,0,0,8,8);
	*/
}

//printing the number of lives left
void printLives(GameStats gameStats){
	int r;
	r = gameStats.healthPoints;
	printNum(3,18,r);

	/*if(l!=0)
		printNum(8,0,l);
	else
		drawSprite(16,0,0,8,8,8);*/
}

void drawOneObject(Object* obj)
{
	int column = obj->column * 16;
	int row = obj->row;

	if(obj->isFlower)
	{
		if(obj->position)
		{
			if(obj->roseOrYellow)
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
			if(obj->roseOrYellow)
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
		if(obj->position)
			drawSprite(column, row, 16, 16, 3, trash_broke.pixel_data);
		else
			drawSprite(column, row, 16, 16, 3, trash.pixel_data);
	}
}

void drawObjectMap(Object* map)
{
	int i,j;
	for(i = 0; i < PATHS; i++)
	{
		for(j = 0; j < MAX_OBJECTS; j++)
		{
			if(map[i * MAX_OBJECTS + j].valid)
			{
				drawOneObject(&map[i * MAX_OBJECTS + j]);
			}
		}
	}
}

void drawEndGame()
{

	unsigned int gameOver[15][20] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,0,0,1,0,0,1,0,0,0,1,0,1,1,1,0},
		{0,1,0,0,0,0,1,0,1,0,1,1,0,1,1,0,1,0,0,0},
		{0,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0},
		{0,1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0},
		{0,1,1,1,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,0},
		{0,1,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0},
		{0,1,0,0,1,0,0,1,0,1,0,0,1,1,1,0,1,1,1,0},
		{0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,1,1,0,0},
		{0,1,1,1,1,0,0,0,1,0,0,0,1,1,1,0,1,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	int row,column;
	bool flag = false;
	while(1)
	{
		for (row = 0; row < 15; row++)
		{
			for (column = 0; column < 20; column++)
			{
				if (gameOver[row][column] == 0)
					drawSprite(column*16, row*16, 16, 16, sky.bytes_per_pixel, sky.pixel_data);
				else if ((gameOver[row][column] == 1) && !flag)
				{
					drawSprite(column*16, row*16, 16, 16, rose_flower_1.bytes_per_pixel, rose_flower_1.pixel_data);
				}else if((gameOver[row][column] == 1) && flag)
				{
					drawSprite(column*16, row*16, 16, 16, rose_flower_2.bytes_per_pixel, rose_flower_2.pixel_data);
				}
			}
		}

		flag = !flag;
		for(int i = 0; i < 50000; i++); // Delay.
	}
}

void startValues(){
	drawSprite(18*16, 0, 16, 16, rose_flower_1.bytes_per_pixel, rose_flower_1.pixel_data);
	drawSprite(19*16, 0, 16, 16, yellow_flower_1.bytes_per_pixel, yellow_flower_1.pixel_data);
	printNum(1,19,0);

	drawSprite(19*16, 3*16, 16, 16, life.bytes_per_pixel, life.pixel_data);
	printNum(3,18,9);
}


