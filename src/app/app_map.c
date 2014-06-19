#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"
#include "std/timer.h"
#include "std/button.h"
#include "app/map.h"

/* dimension of map in characters, to be used in various functions */
#define WIDTH 190
#define HEIGHT 50

/* constants to be used when drawing paddle */
#define PADDLE_HALF_LEN 15
#define PADDLE_STRING "FEDCBA9876543210123456789ABCDEF"

/* constants to be used in collision detection and handling */
#define COLLISION_NONE 0x0
#define COLLISION_HORIZONTAL 0x1
#define COLLISION_VERTICAL 0x2
#define COLLISION_PADDLE 0x3
#define COLLISION_BOTTOM 0x4

/* constants to be used when drawing blocks */
#define BLOCK_ROWS 5
#define BLOCK_PADDING_TOP 4
#define BLOCK_COLUMNS 32 //size of long
#define BLOCK_LENGTH 4
#define BLOCK_HEIGHT 2
#define BLOCK_INTERDIST_X 1
#define BLOCK_INTERDIST_Y 1
#define PRECISION 128

static void draw_borders(void)
{
	struct std_draw_box topb;
	struct std_draw_box leftb;
	struct std_draw_box rightb;
	struct std_draw_box botb;

	topb.tl.x = 1;
	topb.tl.y = 1;
	topb.br.x = WIDTH;
	topb.br.y = 1;
	topb.color = STD_TTY_BCOLOR_GRAY;

	leftb.tl.x = 1;
	leftb.tl.y = 1;
	leftb.br.x = 1;
	leftb.br.y = HEIGHT-1;
	leftb.color = STD_TTY_BCOLOR_GRAY;

	rightb.tl.x = WIDTH;
	rightb.tl.y = 1;
	rightb.br.x = WIDTH;
	rightb.br.y = HEIGHT-1;
	rightb.color = STD_TTY_BCOLOR_GRAY;

	botb.tl.x = 1;
	botb.tl.y = HEIGHT;
	botb.br.x = WIDTH;
	botb.br.y = HEIGHT;
	botb.color = STD_TTY_BCOLOR_GRAY;

	std_draw_box(&leftb);
	std_draw_box(&topb);
	std_draw_box(&rightb);
	//std_draw_box(&botb);
}


static int count_blocks(long *blocks)
{
	int i;
	int j;
	int count = 0;

	for (i = 0; i < BLOCK_ROWS; i++) {
		for (j = 0; j < BLOCK_COLUMNS; j++) {
			if (blocks[i] & (0x80000000 >> j))
				count++;		
		}
	}
	return count;
}

static void draw_blocks(struct app_map_context *ctx)
{
	int i;
	int j;
	int k;
	struct std_draw_box cur_block;
	
	int block_start_x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2;


	static const long maps[3][5] = {
		{0x38000000,0x70000000,0xE6666666,0x70000000,0x38000000},
		{0x55555555,0xAAAAAAAA,0x55555555,0x00000000,0x00000000},
		{0x1F3E7CF8,0x11224488,0x152A54A8,0x11224488,0x1F3E7CF8}
		};
	
	for (i = 0; i < BLOCK_ROWS; i++)
		ctx->blocks[i] = maps[ctx->level-1][i];  // -1 because first level is 1 and first index is 0
	
	ctx->blocks_left = count_blocks(ctx->blocks);
	
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


static void draw_ball(struct app_map_ball *ball)
{
	static int x_old = 6;
	static int y_old = 6;
	int x, y;
	
	x = std_fixpt_f2i(ball->pos.x);
	y = std_fixpt_f2i(ball->pos.y);

	if (x != x_old || y != y_old) {
		/* remove drawing of last ball */
		
		std_tty_gotoxy(x_old, y_old);
		std_tty_set_fcolor(STD_TTY_FCOLOR_BLACK);
		std_tty_printf("o");
	
		/* draw ball at new position */
		std_tty_gotoxy(x, y);
		std_tty_set_fcolor(STD_TTY_FCOLOR_WHITE);
		std_tty_printf("o");

		x_old = x;
		y_old = y;
	}
}

static void draw_paddle(struct app_map_paddle *paddle)
{
	static int x_old = 30;
	int x;

	x = std_fixpt_f2i(paddle->x);


	if (x != x_old) {
		/* remove drawing of last paddle */
		std_tty_gotoxy(x_old-PADDLE_HALF_LEN, HEIGHT);
		std_tty_set_fcolor(STD_TTY_FCOLOR_BLACK);
		std_tty_printf(PADDLE_STRING);
	
		/* draw paddle at new position */
		std_tty_gotoxy(x-PADDLE_HALF_LEN, HEIGHT);
		std_tty_set_fcolor(STD_TTY_FCOLOR_WHITE);
		std_tty_printf(PADDLE_STRING);
		x_old = x;
	}
}

static char test_paddle_collision(struct app_map_ball *ball, 
				struct app_map_paddle *paddle)
{
	int pad_x = std_fixpt_f2i(paddle->x);
	int ball_x = std_fixpt_f2i(ball->pos.x);
	int ball_x_next = std_fixpt_f2i(ball->pos.x + ball->vel.x);
	int ball_y_next = std_fixpt_f2i(ball->pos.y + ball->vel.y);

	if (ball_y_next >= HEIGHT && ball_x_next >= pad_x-PADDLE_HALF_LEN && ball_x_next <= pad_x+PADDLE_HALF_LEN)
		return COLLISION_PADDLE;
	else
		return COLLISION_NONE;

}


static char test_block_collision(struct app_map_context *ctx)
{
	int i;
	int j;
	int k;
	struct std_fixpt_point temp_fpos;
	int temp_posx;
	int temp_posy;
	
	struct std_draw_box cur_block;
	int ball_x = std_fixpt_f2i(ctx->ball.pos.x);  // not 100% about this
	int ball_y = std_fixpt_f2i(ctx->ball.pos.y);
	
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
					do {
						temp_fpos.x -= ctx->ball.vel.x / PRECISION;
						temp_fpos.y -= ctx->ball.vel.y / PRECISION;
						temp_posx = std_fixpt_f2i(temp_fpos.x);
						temp_posy = std_fixpt_f2i(temp_fpos.y);
					} while ((cur_block.tl.x <= temp_posx && temp_posx <= cur_block.br.x) && (cur_block.tl.y <= temp_posy && temp_posy <= cur_block.br.y));
					
					ctx->blocks[i] &= ~(0x80000000 >> j); // remove block from storage
					ctx->blocks_left--;                   // update counter
					ctx->score += ctx->difficulty;        // increase score
					std_draw_box(&cur_block);             // remove block from screen
					std_tty_gotoxy(10,10);
					std_tty_printf("%i", ctx->blocks_left);
					if (!(cur_block.tl.y <= temp_posy && temp_posy <= cur_block.br.y))
						return COLLISION_HORIZONTAL;
					else 
						return COLLISION_VERTICAL;
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

static char test_collision(struct app_map_context *ctx)
{
	char r;
	int ball_x_next = std_fixpt_f2i(ctx->ball.pos.x + ctx->ball.vel.x);
	int ball_y_next = std_fixpt_f2i(ctx->ball.pos.y + ctx->ball.vel.y);

	if (ball_x_next <= 1)
		return COLLISION_VERTICAL;

	else if (ball_x_next >= WIDTH)
		return COLLISION_VERTICAL;

	else if (r = test_block_collision(ctx))
		return r;

	else if (ball_y_next <= 1)
		return COLLISION_HORIZONTAL;

	else if (r = test_paddle_collision(&ctx->ball, &ctx->paddle))
		return r;

	else if (ball_y_next >= HEIGHT)
		return COLLISION_BOTTOM;

	else 
		return COLLISION_NONE;
}

static void handle_paddle_collision(struct app_map_ball *ball, 
				struct app_map_paddle *paddle)
{
	long pad_offset = paddle->x - std_fixpt_i2f(PADDLE_HALF_LEN);
	long pad_len = std_fixpt_i2f(PADDLE_HALF_LEN*2+1);
	long pad_sect_len = pad_len/7;
	long ball_x = ball->pos.x;

	if (ball_x >= pad_offset && ball_x <= (pad_offset + pad_sect_len)) {
		ball->vel.x = ball->speed*std_fixpt_cos(256-32);
		ball->vel.y = -(ball->speed*std_fixpt_sin(256-32));
	} else if (ball_x >= (pad_offset + pad_sect_len) && ball_x <= (pad_offset + 2*pad_sect_len)) {
		ball->vel.x = ball->speed*std_fixpt_cos(256-64);
		ball->vel.y = -(ball->speed*std_fixpt_sin(256-64));
	} else if (ball_x >= (pad_offset + 2*pad_sect_len) && ball_x <= (pad_offset + 3*pad_sect_len)) {
		ball->vel.x = ball->speed*std_fixpt_cos(128+32);
		ball->vel.y = -(ball->speed*std_fixpt_sin(128+32));
	} else if (ball_x >= (pad_offset + 3*pad_sect_len) && ball_x <= (pad_offset + 4*pad_sect_len)) {
		ball->vel.x = ball->speed*std_fixpt_cos(128);
		ball->vel.y = -(ball->speed*std_fixpt_sin(128));
	} else if (ball_x >= (pad_offset + 4*pad_sect_len) && ball_x <= (pad_offset + 5*pad_sect_len)) {
		ball->vel.x = ball->speed*std_fixpt_cos(128-32);
		ball->vel.y = -(ball->speed*std_fixpt_sin(128-32));
	} else if (ball_x >= (pad_offset + 5*pad_sect_len) && ball_x <= (pad_offset + 6*pad_sect_len)) {
		ball->vel.x = ball->speed*std_fixpt_cos(64);
		ball->vel.y = -(ball->speed*std_fixpt_sin(64));
	} else if (ball_x >= (pad_offset + 6*pad_sect_len) && ball_x <= (pad_offset + 7*pad_sect_len)) {
		ball->vel.x = ball->speed*std_fixpt_cos(32);
		ball->vel.y = -(ball->speed*std_fixpt_sin(32));
	}
}
		

static void handle_collision(struct app_map_context *ctx, char coll_type)
{
	switch(coll_type) {
	case COLLISION_VERTICAL:
		ctx->ball.vel.x = -(ctx->ball.vel.x);
		break;
	case COLLISION_PADDLE:
		handle_paddle_collision(&ctx->ball, &ctx->paddle);
		break;
	case COLLISION_HORIZONTAL:
		ctx->ball.vel.y = -(ctx->ball.vel.y);
		break;
	case COLLISION_BOTTOM:
		ctx->ball.vel.x = ctx->ball.speed*0;
		ctx->ball.vel.y = ctx->ball.speed*std_fixpt_i2f(1);
		ctx->ball.pos.x = std_fixpt_i2f(WIDTH/2);
		ctx->ball.pos.y = std_fixpt_i2f(HEIGHT/2);
		ctx->lives--;
	default:
		break;
	}
}

void app_map_reset(struct app_map_context *ctx)
{
		ctx->ball.pos.x = std_fixpt_i2f(WIDTH/2);
		ctx->ball.pos.y = std_fixpt_i2f(HEIGHT/2);
		ctx->ball.speed = 2;
		ctx->ball.vel.x = ctx->ball.speed*0;
		ctx->ball.vel.y = ctx->ball.speed*std_fixpt_i2f(1);
		ctx->paddle.x = std_fixpt_i2f(WIDTH/2);
		ctx->paddle.vel = std_fixpt_i2f(3)/1;
		std_tty_clrscr();
		draw_borders();
		draw_blocks(ctx);
}

void app_map_refresh(struct app_map_context *ctx)
{
	char collision;
	if (collision = test_collision(ctx))
		handle_collision(ctx, collision);
	ctx->ball.pos.x += ctx->ball.vel.x;
	ctx->ball.pos.y += ctx->ball.vel.y;
	draw_ball(&ctx->ball);
	switch (std_button_pressed()) {
		case STD_BUTTON_LEFT:
			if (std_fixpt_f2i(ctx->paddle.x-ctx->paddle.vel)-PADDLE_HALF_LEN <= 1)
				ctx->paddle.x = std_fixpt_i2f(1+PADDLE_HALF_LEN);
			else
				ctx->paddle.x -= ctx->paddle.vel;
			break;
		case STD_BUTTON_RIGHT:
			if (std_fixpt_f2i(ctx->paddle.x+ctx->paddle.vel)+PADDLE_HALF_LEN >= WIDTH)
				ctx->paddle.x = std_fixpt_i2f(WIDTH-PADDLE_HALF_LEN);
			else
				ctx->paddle.x += ctx->paddle.vel;
			break;
		default:
			break;
	}
	draw_paddle(&ctx->paddle);
}
