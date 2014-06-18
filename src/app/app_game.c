#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"
#include "std/fixpt.h"
#include "app/game.h"
#include "app/map.h"


void game_tick (struct app_map_context *ctx)
{
	//
	//
	//  Troels kode om collision detection, skal operere på app_map_context.
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	
	if (ctx->blocks_left == 0) {
		ctx->level++;
		init_level(ctx);
	}
	
	if (ctx->lives == 0);
		//init_endgame(ctx); //  HENRIKS FUNKTION OM HIGHSCORE
		
}

void init_level(struct app_map_context *ctx) {
	draw_blocks(ctx);
	ctx->ball.vel.x = std_fixpt_i2f(1)/32;
	ctx->ball.vel.y = -std_fixpt_i2f(1)/32;
	ctx->ball.pos.x = 30;
	ctx->ball.pos.y = 30;
	ctx->paddle.x = 30;
	ctx->paddle.vel = 1;
}

void init_game(struct app_map_context *ctx) {
	ctx->level = 1;
	ctx->score = 0;
	ctx->lives = 3;
	
	app_map_reset(ctx);
	game_state = IN_GAME;
}

draw_blocks(struct app_map_context *ctx)
{
	int i;
	int j;
	int k;
	struct std_draw_box cur_block;
	
	int block_start_x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2;
	
	for (i = 0; i < BLOCK_ROWS; i++)
		ctx->blocks[i] = maps[ctx->level][i];
	
	
	cur_block.tl.x = block_start_x;
	cur_block.tl.y = BLOCK_PADDING_TOP;
	cur_block.br.x = cur_block.tl.x + (BLOCK_LENGTH - 1);
	cur_block.br.y = cur_block.tl.y + (BLOCK_HEIGHT -1);
	cur_block.color = STD_TTY_BCOLOR_GRAY;
	
	for (i = 0; i < BLOCK_ROWS; i++) {
		for (j = 0; j < BLOCK_COLUMNS; j++) {
			if(ctx->blocks[i] & (0x80000000 >> j)) {
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
}

char test_block_collision(struct app_map_context *ctx)
{
	int i;
	int j;
	int k;
	struct std_fixpt_point temp_fpos;
	int temp_posx;
	int temp_posy;
	
	struct std_draw_box cur_block;
	int ball_x = std_fixpt_f2i(ctx->ball.pos.x) + 1;  // not 100% about this
	int ball_y = std_fixpt_f2i(ctx->ball.pos.y) + 1;
	
	int block_start_x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2;
	
	cur_block.tl.x = block_start_x;
	cur_block.tl.y = BLOCK_PADDING_TOP;
	cur_block.br.x = cur_block.tl.x + (BLOCK_LENGTH - 1);
	cur_block.br.y = cur_block.tl.y + (BLOCK_HEIGHT -1);
	cur_block.color = STD_TTY_BCOLOR_BLACK; // simply delete block
	
	for (i = 0; i < BLOCK_ROWS; i++) {
		for (j = 0; j < BLOCK_COLUMNS; j++) {
			if(ctx->blocks[i] & (0x80000000 >> j)) // test if there is block
				if ((cur_block.tl.x <= ball_x && ball_x <= cur_block.br.x) && (cur_block.tl.y <= ball_y && ball_y <= cur_block.br.y)) {
					temp_fpos = ctx->ball.pos;
					temp_posx = std_fixpt_f2i(temp_fpos.x) + 1;
					temp_posy = std_fixpt_f2i(temp_fpos.y) + 1;
					while ((cur_block.tl.x <= temp_posx && temp_posx <= cur_block.br.x) && (cur_block.tl.y <= temp_posy && temp_posy <= cur_block.br.y)) {
						temp_fpos.x -= ctx->ball.vel.x / PRECISION;
						temp_fpos.y -= ctx->ball.vel.y / PRECISION;
						temp_posx = std_fixpt_f2i(temp_fpos.x) + 1;
						temp_posy = std_fixpt_f2i(temp_fpos.y) + 1;
					}
					ctx->blocks[i] &= ~(0x80000000 >> j);
					std_draw_box(&cur_block); // delete block
					std_tty_gotoxy(10,10);
					std_tty_printf("success");
					if (!(cur_block.tl.y <= temp_posy && temp_posy <= cur_block.br.y))
						return COLLISION_HORIZONTAL;
						//return COLLISION_VERTICAL;
					else 
						return COLLISION_VERTICAL;
						//return COLLISION_HORIZONTAL;
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

int count_blocks(long *blocks)
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

