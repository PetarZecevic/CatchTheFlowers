/*
 * sprite.h
 *
 *  Created on: May 26, 2019
 *      Author: Petar
 */

#ifndef SPRITE_H_
#define SPRITE_H_

typedef struct{
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char	 pixel_data[16 * 16 * 3 + 1];
}BackgroundSprite;

typedef struct{
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char	 pixel_data[48 * 80 * 3 + 1];
}BunnySprite;

typedef struct{
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char	 pixel_data[16 * 16 * 3 + 1];
}ItemSprite;

#endif /* SPRITE_H_ */
