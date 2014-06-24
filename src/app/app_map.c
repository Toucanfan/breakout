#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"
#include "std/timer.h"
#include "std/button.h"
#include "std/rom.h"
#include "app/map.h"
#include "app/draw.h"

/* dimension of map in characters, to be used in various functions */
#define WIDTH 190
#define HEIGHT 50

/* constants to be used when drawing paddle */
#define PADDLE_HALF_LEN 15
#define PADDLE_STRING "                               "

/* constants to be used in collision detection and handling */
#define COLLISION_NONE 0x0
#define COLLISION_HORIZONTAL 0x1
#define COLLISION_VERTICAL 0x2
#define COLLISION_PADDLE 0x3
#define COLLISION_BOTTOM 0x4

/* constants to be used when drawing blocks */
#define BLOCK_PADDING_TOP 4
#define BLOCK_COLUMNS 32 //!<size of long
#define BLOCK_LENGTH 4
#define BLOCK_HEIGHT 3
#define BLOCK_INTERDIST_X 1
#define BLOCK_INTERDIST_Y 1
#define PRECISION 128
//! Expression testing if the ball is within the x-components of the block
#define BALL_WITHIN_BLOCK_X (x <= std_fixpt_f2i(ball_pos_x_next) && std_fixpt_f2i(ball_pos_x_next) <= x + (BLOCK_LENGTH-1))
//! Expression testing if the ball is within the y-components of the block
#define BALL_WITHIN_BLOCK_Y (y <= std_fixpt_f2i(ball_pos_y_next) && std_fixpt_f2i(ball_pos_y_next) <= y + (BLOCK_HEIGHT-1))

#define MAPS 3

//! Draws the borders of the map
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
	//std_draw_box(&botb);           // TROELS KIG HER WTF ER DET?
}

//! Counts the number of blocks left
/**
 * @param blocks The map (a pointer to longs)
 *
 * @return The number of blocks
 */
static int count_blocks(long *blocks)
{
	char i;
	char j;
	int count = 0;

	for (i = 0; i < BLOCK_ROWS; i++) {
		for (j = 0; j < BLOCK_COLUMNS; j++) {
			if (blocks[i] & (0x80000000 >> j))
				count++;		
		}
	}
	return count;
}

//! Draws or erases a block
/**
 * @param row The row to draw on
 * @param column The column to draw on
 * @param draw Boolean char for drawing or erasing
 */
void draw_block(char row, char column, char draw)
{
	int x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2 + column * (BLOCK_LENGTH+BLOCK_INTERDIST_X); // start position
	int y = BLOCK_PADDING_TOP + (BLOCK_INTERDIST_Y + BLOCK_HEIGHT) * row;
	int i;
	int j;
	
	if (draw)
		std_tty_set_bcolor(STD_TTY_BCOLOR_GREEN);
	else
		std_tty_set_bcolor(STD_TTY_BCOLOR_BLACK); // remove block
	
	for (i = 0; i < BLOCK_HEIGHT; i++) {
		std_tty_gotoxy(x,y+i);
		for (j = 0; j < BLOCK_LENGTH; j++)
			std_tty_printf(" ");
	}
	std_tty_set_bcolor(STD_TTY_BCOLOR_BLACK);
}

//! Tests if the ball collides with a block
/**
 * @param row The row to check
 * @param column The column to check
 * @param ctx The game context
 *
 * @return Collision type
 */
char test_block(char row, char column, struct app_map_context *ctx)
{	
	int x = WIDTH / 2 - BLOCK_COLUMNS * (BLOCK_LENGTH+BLOCK_INTERDIST_X) / 2 + column * (BLOCK_LENGTH+BLOCK_INTERDIST_X); // start position
	int y = BLOCK_PADDING_TOP + (BLOCK_INTERDIST_Y + BLOCK_HEIGHT) * row;
	
	long ball_pos_x_next = ctx->ball.pos.x + ctx->ball.vel.x;
	long ball_pos_y_next = ctx->ball.pos.y + ctx->ball.vel.y;
	

	if (BALL_WITHIN_BLOCK_X && BALL_WITHIN_BLOCK_Y) {
		while (BALL_WITHIN_BLOCK_X && BALL_WITHIN_BLOCK_Y) {
			ball_pos_x_next -= ctx->ball.vel.x / PRECISION;
			ball_pos_y_next -= ctx->ball.vel.y / PRECISION;
		}	
		if (BALL_WITHIN_BLOCK_X)
			return COLLISION_HORIZONTAL;
		else
			return COLLISION_VERTICAL;
	}
	
	return COLLISION_NONE;
}

//! Draws all blocks
/**
 * @param ctx The game context
 */
static void draw_blocks(struct app_map_context *ctx)
{
	int i;
	int j;

	static const long maps[MAPS][BLOCK_ROWS] = {
		{0x38000000,0x70000000,0x66666666,0x70000000,0x38000000},
		{0x55555555,0xAAAAAAAA,0x55555555,0x00000000,0x00000000},
		{0x1F3E7CF8,0x11224488,0x152A54A8,0x11224488,0x1F3E7CF8}
		};
	
	if (ctx->resumed_game != 1) {
		for (i = 0; i < BLOCK_ROWS; i++)
			ctx->blocks[i] = maps[ctx->level-1][i];  // -1 because first level is 1 and first index is 0
		ctx->blocks_left = count_blocks(ctx->blocks);
	}

	for (i = 0; i < BLOCK_ROWS; i++)
		for (j = 0; j < BLOCK_COLUMNS; j++)
			if(ctx->blocks[i] & (0x80000000 >> j))  // only draw block if relevant bit is 1
				draw_block(i,j,1);
}

//! Draws a ball
/**
 * @param ball The ball struct
 */
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

//! Resets the paddle
/**
 * @param paddle The paddle struct
 */
static void reset_paddle(struct app_map_paddle *paddle)
{
	int x = WIDTH/2;

	std_tty_gotoxy(x-PADDLE_HALF_LEN, HEIGHT);
	std_tty_set_bcolor(STD_TTY_FCOLOR_GRAY);
	std_tty_printf(PADDLE_STRING);

	std_tty_set_bcolor(STD_TTY_BCOLOR_BLACK);
	paddle->x = std_fixpt_i2f(x);

}

//! Draws the paddle
/**
 * @param paddle The paddle struct
 */
static void draw_paddle(struct app_map_paddle *paddle)
{
	static int x_old = WIDTH/2;
	int x;
	int delta_x;
	int i;
	char spaces[8];

	for (i = 0; i < sizeof(spaces)-1; i++)
		spaces[i] = ' ';
	spaces[sizeof(spaces)-1] = '\0';

	x = std_fixpt_f2i(paddle->x);
	delta_x = x-x_old;
	spaces[delta_x] = '\0';

	/* do nothing if paddle has not moved since last time called */
	if (delta_x == 0)
		return;

	else if (delta_x > 0) {
		/* remove drawing of last paddle */
		std_tty_set_bcolor(STD_TTY_BCOLOR_BLACK);
		std_tty_gotoxy(x_old-PADDLE_HALF_LEN, HEIGHT);
		std_tty_puts(spaces);
	
		/* draw paddle at new position */
		std_tty_set_bcolor(STD_TTY_BCOLOR_GRAY);
		std_tty_gotoxy(x+PADDLE_HALF_LEN-delta_x+1, HEIGHT);
		std_tty_puts(spaces);

	} else if (delta_x < 0) {
		delta_x = -delta_x;
		/* remove drawing of last paddle */
		std_tty_set_bcolor(STD_TTY_BCOLOR_BLACK);
		std_tty_gotoxy(x_old+PADDLE_HALF_LEN-delta_x+1, HEIGHT);
		std_tty_puts(spaces);

		/* draw paddle at new position */
		std_tty_set_bcolor(STD_TTY_BCOLOR_GRAY);
		std_tty_gotoxy(x-PADDLE_HALF_LEN, HEIGHT);
		std_tty_puts(spaces);
	}
		
	/* remember new position for next time */
	x_old = x;
	std_tty_set_bcolor(STD_TTY_BCOLOR_BLACK);
}

//! Tests for paddle collision
/**
 * @param ball The ball struct
 * @param paddle The paddle struct
 *
 * @return Collision type
 */
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

//! Tests for block collisions
/**
 * @param ctx The game context
 *
 * @return Collision type
 */
static char test_block_collision(struct app_map_context *ctx)
{
	int i;
	int j;
	char collision;

	for (i = 0; i < BLOCK_ROWS; i++)
		for (j = 0; j < BLOCK_COLUMNS; j++)
			if (ctx->blocks[i] & (0x80000000 >> j)) { // test if there is block
				collision = test_block(i,j,ctx);
				if (collision) {
					draw_block(i,j,0); // remove block from screen
					ctx->blocks[i] &= ~(0x80000000 >> j); // turn off relevant block bit
					ctx->score += ctx->difficulty;
					ctx->blocks_left--;
					return collision;
				}
			}
	return COLLISION_NONE;
}

//! Tests for collisions
/**
 * Tests for collisions between ball and blocks and paddle.
 *
 * @param ctx The game context
 *
 * @return Collision type
 */
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

//! Handle paddle collision
/**
 * @param ball The ball struct
 * @param paddle The paddle struct
 */
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

//! Handle collisions
/**
 * @param ctx The game context
 * @param coll_type The type of collision
 */
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

//! Save the game state
/**
 * @param ctx The game context
 */
void save_game(struct app_map_context *ctx)
{	
	app_draw_save();
	ctx->resumed_game = 1;
	std_rom_write(STD_ROM_PAGE1, ctx, sizeof(*ctx));
	ctx->resumed_game = 0;
}

//! Reset the map, ball and paddle
/**
 * @param ctx The game context
 */
void app_map_reset(struct app_map_context *ctx)
{		
		std_tty_clrscr();
		draw_borders();
		draw_blocks(ctx);
		if (ctx->resumed_game == 1) {
			ctx->resumed_game = 0;
			return;
		}
		ctx->ball.speed = 1;
		ctx->ball.vel.x = ctx->ball.speed*0;
		ctx->ball.vel.y = ctx->ball.speed*std_fixpt_i2f(1);
		ctx->paddle.vel = std_fixpt_i2f(3)/1;
		ctx->ball.pos.x = std_fixpt_i2f(WIDTH/2);
		ctx->ball.pos.y = std_fixpt_i2f(HEIGHT/2);

		reset_paddle(&ctx->paddle);
}

//! Refresh the ball and paddle
/**
 * @param ctx The game context 
 */
void app_map_refresh(struct app_map_context *ctx)
{
	char collision;

	/* handle eventual collissions that may occur if we add 'vel' to it */
	if (collision = test_collision(ctx))
		handle_collision(ctx, collision);

	/* add 'vel' to position to get new position */
	ctx->ball.pos.x += ctx->ball.vel.x;
	ctx->ball.pos.y += ctx->ball.vel.y;
	draw_ball(&ctx->ball);

	/* handle eventual button press */
	switch (std_button_pressed()) {
		case STD_BUTTON_LEFT:
			/* if paddle is to move out of bounds, reset it to
			 * leftmost position */
			if (std_fixpt_f2i(ctx->paddle.x-ctx->paddle.vel)-PADDLE_HALF_LEN <= 1)
				ctx->paddle.x = std_fixpt_i2f(1+PADDLE_HALF_LEN);
			else
				ctx->paddle.x -= ctx->paddle.vel;
			break;
		case STD_BUTTON_RIGHT:
			/* if paddle is to move out of bounds, reset it to
			 * rightmost position */
			if (std_fixpt_f2i(ctx->paddle.x+ctx->paddle.vel)+PADDLE_HALF_LEN >= WIDTH)
				ctx->paddle.x = std_fixpt_i2f(WIDTH-PADDLE_HALF_LEN);
			else
				ctx->paddle.x += ctx->paddle.vel;
			break;
		case STD_BUTTON_MIDDLE:
			save_game(ctx);
		default:
			break;
	}
	draw_paddle(&ctx->paddle);
}
