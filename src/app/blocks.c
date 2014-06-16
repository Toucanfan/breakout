#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"

#define BLOCK_ROWS 3
#define BLOCK_PADDING_TOP 4
#define BLOCK_COLUMNS 32 //size of long
#define BLOCK_LENGTH 2
#define BLOCK_INTERDIST_X 1
#define BLOCK_INTERDIST_Y 1

#define WIDTH 170
#define HEIGHT 60

void app_map_draw_blocks(void) {
	static long blocks[BLOCK_ROWS] = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF}; // 1 bit per block
	int i;
	int j;
	int k;
	struct std_draw_box cur_block;
	
	int block_start_x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2;
	
	cur_block.tl.x = block_start_x
	cur_block.tl.y = BLOCK_PADDING_TOP;
	cur_block.br.x = cur_block.tl.x + (BLOCK_LENGTH - 1);
	cur_block.br.y = cur_block.tl.y;
	cur_block.color = STD_TTY_BCOLOR_GRAY;
	
	for (i = 0; i < BLOCK_ROWS; i++) {
		for (j = 0; j < BLOCK_COLUMNS; j++) {
			if(blocks[i] & (0x80000000 >> j)) {
				std_draw_box(&cur_block);
				for (k = 1; k <= BLOCK_INTERDIST_X; k++) {
					std_tty_gotoxy(cur_block.br.x+k,cur_block.br.y);
					std_tty_printf(" "); // blank box
				}
			} else {
				for (k = 0; k <= BLOCK_INTERDIST_X + BLOCK_LENGTH; k++) {
					std_tty_gotoxy(cur_block.tl.x+k,cur_block.tl.y);
					std_tty_printf(" "); // blank box
				}
			}
			cur_block.tl.x += BLOCK_INTERDIST_X + BLOCK_LENGTH;
			cur_block.br.x += BLOCK_INTERDIST_X + BLOCK_LENGTH;
		}	
		cur_block.tl.x = block_start_x;
		cur_block.br.x = cur_block.tl.x + (BLOCK_LENGTH-1);
		cur_block.tl.y += (BLOCK_INTERDIST_Y + 1);
		cur_block.br.y += (BLOCK_INTERDIST_Y + 1);
		
	}		
}