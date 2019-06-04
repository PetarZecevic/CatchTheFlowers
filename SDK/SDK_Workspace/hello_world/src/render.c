#include "render.h"

#include "vga_periph_mem.h"
#include "xparameters.h"

const BunnySprite bunny_left_1, bunny_left_2, bunny_right_1, bunny_right_2,
	bunny_stable, bunny_transit_1, /*bunny_transit_2,*/ bunny_down_1;

void init()
{

	VGA_PERIPH_MEM_mWriteMemory(
				XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x00, 0x0); // direct mode   0
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0x3); // display_mode  1
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x08, 0x0); // show frame      2
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x0C, 0xff); // font size       3
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xFFFFFF); // foreground 4
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14,0x008000); // background color 5
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF0000); // frame color      6
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 1);
}

// Drawing RGB 565 format.
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
	case CENTER:
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
	/*
	case TRANSIT2:
		drawSprite(col, row, 48, 80, bunny_transit_2.bytes_per_pixel, bunny_transit_2.pixel_data);
		break;
	*/
	case DOWN1:
		drawSprite(col, row, 48, 80, bunny_down_1.bytes_per_pixel, bunny_down_1.pixel_data);
		break;
	/*
	case HURT1:
		drawSprite(col, row, 48, 80, bunny_hurt_2.bytes_per_pixel, bunny_hurt_2.pixel_data);
		break;
	case HURT2:
		drawSprite(col, row, 48, 80, bunny_hurt_2.bytes_per_pixel, bunny_hurt_2.pixel_data);
		break;
	*/
	default:
		break;
	}
}
