#include "gameplay.h"
#include <time.h>
#include <stdlib.h>
#include "platform.h"

const BackgroundSprite ground, sky;

void test()
{
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

	Bunny bunnies[3];

	Bunny_Init(&bunnies[0], 10, 2);
	Bunny_Init(&bunnies[1], 10, 9);
	Bunny_Init(&bunnies[2], 10, 15);

	while(1)
	{
		// Delay.
		for(int i = 0; i < 1500000; i++);
		for(int j = 0; j < 3; j++)
		{
			drawBunny(&bunnies[j]);
			Bunny_ChangeFrame(&bunnies[j]);
		}
	}
}

int main()
{

	// Ima bug kada se desi da pada kamen na otvorenu kutijicu.
	// Tada ne azurira broj osvojenih poena.
	srand(time(NULL));
	cleanup_platform();

	init_platform();
	init();

	//gameLoop();
	//drawEndGame();

	test();
	return 0;
}


