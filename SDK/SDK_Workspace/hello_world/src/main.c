#include "gameplay.h"
#include <time.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"

int main() {

	srand(time(NULL));
	cleanup_platform();

	init_platform();
	init();

	gameLoop();
	drawEndGame();

	return 0;
}


