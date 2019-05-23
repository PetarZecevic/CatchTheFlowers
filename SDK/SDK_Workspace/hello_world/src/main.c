#include "gameplay.h"
#include <time.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"


void test()
{
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 20; j++){
			if(i < 13)
			{
				drawSky(0,0,j*16,i*16,16,16);
			}
			else
			{
				drawGround(0,0,j*16,i*16,16,16);
			}
		}
	}

	int bunnyColumn[3] = {2*16, 9*16, 15*16};
	int bunny = 1;
	while(1){
		for(int i = 0; i < 3000000; i++);
		for(int j = 0; j < 3; j++)
			drawBunny(0,0,bunnyColumn[j],160,48,80,bunny);
		bunny += 1;
		bunny = bunny % 2;
	}
}

int main() {

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


