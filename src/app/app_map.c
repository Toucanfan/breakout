#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"
#include "std/timer.h"
#include "std/button.h"
#include "std/rom.h"
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
#define BLOCK_HEIGHT 3
#define BLOCK_INTERDIST_X 1
#define BLOCK_INTERDIST_Y 1
#define PRECISION 128
#define BALL_WITHIN_BLOCK_X (x <= std_fixpt_f2i(ball_pos_x_next) && std_fixpt_f2i(ball_pos_x_next) <= x + (BLOCK_LENGTH-1))
#define BALL_WITHIN_BLOCK_Y (y <= std_fixpt_f2i(ball_pos_y_next) && std_fixpt_f2i(ball_pos_y_next) <= y + (BLOCK_HEIGHT-1))

#define MAPS 3

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


static void draw_blocks(struct app_map_context *ctx)
{
	int i;
	int j;

	static const long maps[MAPS][BLOCK_ROWS] = {
		{0x38000000,0x70000000,0x66666666,0x70000000,0x38000000},
		{0x55555555,0xAAAAAAAA,0x55555555,0x00000000,0x00000000},
		{0x1F3E7CF8,0x11224488,0x152A54A8,0x11224488,0x1F3E7CF8}
		};
	
	if (!ctx->resumed_game) {
		for (i = 0; i < BLOCK_ROWS; i++)
			ctx->blocks[i] = maps[ctx->level-1+2][i];  // -1 because first level is 1 and first index is 0
		
		ctx->blocks_left = count_blocks(ctx->blocks);
	}

	for (i = 0; i < BLOCK_ROWS; i++)
		for (j = 0; j < BLOCK_COLUMNS; j++)
			if(ctx->blocks[i] & (0x80000000 >> j))  // only draw block if relevant bit is 1
				draw_block(i,j,1);
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

void save_game(struct app_map_context *ctx)
{
	ctx->resumed_game = 1;
	std_rom_write(STD_ROM_PAGE1, ctx, sizeof(*ctx));
	ctx->resumed_game = 0;
	std_tty_gotoxy(30,30);
	std_tty_printf("success");
}

void app_map_reset(struct app_map_context *ctx)
{		
		std_tty_clrscr();
		draw_borders();
		draw_blocks(ctx);
		if (ctx->resumed_game)
			return;
				ctx->ball.speed = 1;
		ctx->ball.vel.x = ctx->ball.speed*0;
		ctx->ball.vel.y = ctx->ball.speed*std_fixpt_i2f(1);
		ctx->paddle.vel = std_fixpt_i2f(3)/1;
		ctx->ball.pos.x = std_fixpt_i2f(WIDTH/2);
		ctx->ball.pos.y = std_fixpt_i2f(HEIGHT/2);
		ctx->paddle.x = std_fixpt_i2f(WIDTH/2);
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
		case STD_BUTTON_MIDDLE:
			save_game(ctx);
		default:
			break;
	}
	draw_paddle(&ctx->paddle);
}
