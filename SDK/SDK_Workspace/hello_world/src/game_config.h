#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_

#include <stdbool.h>
#include "characters.h"
#include "controls.h"

#define SIZEROW 15
#define SIZECOLUMN 20

typedef struct{
	int healthPoints;
	int coinsCollected;
}GameStats;

// Map 1
unsigned char map1Origin[SIZEROW][SIZECOLUMN] = {
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G','G'},
	{'G','G','D','G','G','G','G','G','G','G','D','G','G','G','G','G','G','D','G','G'},
};

// game Over
unsigned char gameOver[SIZEROW][SIZECOLUMN] = {
	{'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D'},
	{'D',0,0,0,0,'D',0,0,0,'D',0,'D','D','D',0,'D',0,0,0,'D'},
	{'D',0,'D','D',0,'D',0,'D',0,'D',0,0,'D',0,0,'D',0,'D','D','D'},
	{'D',0,'D','D','D','D',0,'D',0,'D',0,'D',0,'D',0,'D',0,'D','D','D'},
	{'D',0,'D',0,0,'D',0,0,0,'D',0,'D',0,'D',0,'D',0,0,'D','D'},
	{'D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,'D','D','D'},
	{'D',0,0,0,0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,0,0,'D'},
	{'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D'},
	{'D','D',0,0,0,0,'D',0,'D',0,'D',0,0,0,'D',0,0,0,'D','D'},
	{'D','D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,'D','D'},
	{'D','D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,'D','D'},
	{'D','D',0,'D','D',0,'D',0,'D',0,'D',0,0,'D','D',0,0,0,'D','D'},
	{'D','D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,0,'D','D','D'},
	{'D','D',0,0,0,0,'D','D',0,'D','D',0,0,0,'D',0,'D',0,'D','D'},
	{'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D'},
};

bool mapChanges[SIZEROW][SIZECOLUMN]={
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
	{true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
};

#endif /* GAME_CONFIG_H_ */
