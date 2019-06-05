#include "gameplay.h"
#include "platform.h"
#include "stdlib.h"

int main()
{
	cleanup_platform();

	init_platform();
	init();

	gameLoop();

	return 0;
}
