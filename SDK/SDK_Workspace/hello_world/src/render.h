#ifndef RENDER_H_
#define RENDER_H_

#include "bunny.h"
#include "sprite.h"

// Init graphics.
void init();
// We consider row and column as sprite of dimension 16x16.
void drawBackgroundSprite(unsigned int row, unsigned int column, const BackgroundSprite background);
void drawBunny(Bunny* bunny);

#endif /* RENDER_H_ */
