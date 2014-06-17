#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"
#include "std/fixpt.h"

#define BLOCK_ROWS 3
#define BLOCK_PADDING_TOP 4
#define BLOCK_COLUMNS 32 //size of long
#define BLOCK_LENGTH 4
#define BLOCK_HEIGHT 2
#define BLOCK_INTERDIST_X 1
#define BLOCK_INTERDIST_Y 1

#define COLLISION_NONE 0x0
#define COLLISION_HORIZONTAL 0x1
#define COLLISION_VERTICAL 0x2

#define WIDTH 170
#define HEIGHT 60

static struct ball {
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
};

long *draw_blocks(void)
{
	static long blocks[BLOCK_ROWS] = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF}; // 1 bit per block
	int i;
	int j;
	int k;
	struct std_draw_box cur_block;
	
	int block_start_x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2;
	
	cur_block.tl.x = block_start_x;
	cur_block.tl.y = BLOCK_PADDING_TOP;
	cur_block.br.x = cur_block.tl.x + (BLOCK_LENGTH - 1);
	cur_block.br.y = cur_block.tl.y + (BLOCK_HEIGHT -1);
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
		cur_block.tl.y += (BLOCK_INTERDIST_Y + BLOCK_HEIGHT);
		cur_block.br.y += (BLOCK_INTERDIST_Y + BLOCK_HEIGHT);
	}
	std_tty_gotoxy(40,20);
	std_tty_printf("done");
	return blocks;
}

char test_block_collision(struct ball *ball, long *blocks)
{
	int i;
	int j;
	int k;
	struct std_fixpt_point temp_fpos;
	int temp_posx;
	int temp_posy;
	
	struct std_draw_box cur_block;
	int ball_x = std_fixpt_f2i(ball->pos.x) + 1;  // not 100% about this
	int ball_y = std_fixpt_f2i(ball->pos.y) + 1;
	
	int block_start_x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2;
	
	cur_block.tl.x = block_start_x;
	cur_block.tl.y = BLOCK_PADDING_TOP;
	cur_block.br.x = cur_block.tl.x + (BLOCK_LENGTH - 1);
	cur_block.br.y = cur_block.tl.y + (BLOCK_HEIGHT -1);
	cur_block.color = STD_TTY_BCOLOR_BLACK; // simply delete block
	
	for (i = 0; i < BLOCK_ROWS; i++) {
		for (j = 0; j < BLOCK_COLUMNS; j++) {
			if(blocks[i] & (0x80000000 >> j)) // test if there is block
				if ((cur_block.tl.x <= ball_x && ball_x <= cur_block.br.x) && (cur_block.tl.y <= ball_y && ball_y <= cur_block.br.y)) {
					temp_fpos;
					temp_fpos = ball->pos;
					temp_posx = std_fixpt_f2i(temp_fpos.x);
					temp_posy = std_fixpt_f2i(temp_fpos.y);
					while ((cur_block.tl.x <= temp_posx && temp_posx <= cur_block.br.x) && (cur_block.tl.y <= temp_posy && temp_posy <= cur_block.br.y)) {
						temp_fpos.x -= ball->vel.x / 5;
						temp_fpos.y -= ball->vel.y / 5;
						temp_posx = std_fixpt_f2i(temp_fpos.x) + 1;
						temp_posy = std_fixpt_f2i(temp_fpos.y) + 1;
					}
					blocks[i] &= ~(0x80000000 >> j);
					std_draw_box(&cur_block); // delete block
					std_tty_gotoxy(10,10);
					std_tty_printf("success");
					if (!(cur_block.tl.x < ball_x && ball_x < cur_block.br.x))
						return COLLISION_VERTICAL;
					else 
						return COLLISION_HORIZONTAL;
				}
			cur_block.tl.x += BLOCK_INTERDIST_X + BLOCK_LENGTH;
			cur_block.br.x += BLOCK_INTERDIST_X + BLOCK_LENGTH;
		}	
		cur_block.tl.x = block_start_x;
		cur_block.br.x = cur_block.tl.x + (BLOCK_LENGTH-1);
		cur_block.tl.y += (BLOCK_INTERDIST_Y + BLOCK_HEIGHT);
		cur_block.br.y += (BLOCK_INTERDIST_Y + BLOCK_HEIGHT);
	}		
	
	return COLLISION_NONE;
}

int blocks_left(long *blocks)
{
	int i;
	int j;
	int count;

	for (i = 0; i < BLOCK_ROWS; i++) {
		for (j = 0; j < BLOCK_COLUMNS; j++) {
			if (blocks[i] & (0x80000000 >> j))
				count++;
		}
	}
	return count;
}

