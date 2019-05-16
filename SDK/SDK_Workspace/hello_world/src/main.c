#include "gameplay.h"
#include <time.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"

int main() {

	// Ima bug kada se desi da pada kamen na otvorenu kutijicu.
	// Tada ne azurira broj osvojenih poena.
	srand(time(NULL));
	cleanup_platform();

	init_platform();
	init();

	gameLoop();
	drawEndGame();

	return 0;
}


