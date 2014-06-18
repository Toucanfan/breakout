#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"
#include "std/timer.h"
#include "std/button.h"

extern long *draw_blocks(void);
extern char test_block_collision(struct ball *ball, long *block_locations);

#define WIDTH 190
#define HEIGHT 50
#define PADDLE_HALF_LEN 15
#define PADDLE_STRING "FEDCBA9876543210123456789ABCDEF"

#define COLLISION_NONE 0x0
#define COLLISION_HORIZONTAL 0x1
#define COLLISION_VERTICAL 0x2
#define COLLISION_PADDLE 0x3
#define COLLISION_BOTTOM 0x4

static struct ball {
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
	char speed;
};

static struct paddle {
	long x;
	long vel;
};

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

static void draw_ball(struct ball *ball)
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

static void draw_paddle(struct paddle *paddle)
{
	static int x_old = 10;
	int x;

	x = std_fixpt_f2i(paddle->x);

	if (x-PADDLE_HALF_LEN <= 1) {
		paddle->x = std_fixpt_i2f(x_old);
		x = x_old-1;
	} else if (x+PADDLE_HALF_LEN >= WIDTH) {
		paddle->x = std_fixpt_i2f(x_old);
		x = x_old+1;
	}

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

static char test_paddle_collision(struct ball *ball, struct paddle *paddle)
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

static char test_collision(struct ball *ball, long *block_locations, struct paddle *paddle)
{
	char r;
	int ball_x_next = std_fixpt_f2i(ball->pos.x + ball->vel.x);
	int ball_y_next = std_fixpt_f2i(ball->pos.y + ball->vel.y);

	if (ball_x_next <= 1)
		return COLLISION_VERTICAL;

	else if (ball_x_next >= WIDTH)
		return COLLISION_VERTICAL;

	else if (r = test_block_collision(ball, block_locations))
		return r;

	else if (ball_y_next <= 1)
		return COLLISION_HORIZONTAL;

	else if (r = test_paddle_collision(ball, paddle))
		return r;

	else if (ball_y_next >= HEIGHT)
		return COLLISION_BOTTOM;

	else 
		return COLLISION_NONE;
}

static void handle_paddle_collision(struct ball *ball, struct paddle *paddle)
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
		

static void handle_collision(struct ball *ball, struct paddle *paddle, char coll_type)
{
	switch(coll_type) {
	case COLLISION_VERTICAL:
		ball->vel.x = -(ball->vel.x);
		break;
	case COLLISION_PADDLE:
		handle_paddle_collision(ball, paddle);
		break;
	case COLLISION_HORIZONTAL:
		ball->vel.y = -(ball->vel.y);
		break;
	case COLLISION_BOTTOM:
		ball->vel.x = ball->speed*0;
		ball->vel.y = ball->speed*std_fixpt_i2f(1);
		ball->pos.x = std_fixpt_i2f(WIDTH/2);
		ball->pos.y = std_fixpt_i2f(HEIGHT/2);
	default:
		break;
	}
}

void app_map_refresh(char should_reset, struct game_condition *game_condition)
{
	static struct ball ball;
	static struct paddle paddle;
	static long *block_locations;
	char collision;
	if (should_reset) {
		ball.pos.x = std_fixpt_i2f(WIDTH/2);
		ball.pos.y = std_fixpt_i2f(HEIGHT/2);
		ball.speed = 2;
		ball.vel.x = ball.speed*0;
		ball.vel.y = ball.speed*std_fixpt_i2f(1);
		paddle.x = std_fixpt_i2f(WIDTH/2);
		paddle.vel = std_fixpt_i2f(3)/1;
		std_tty_clrscr();
		draw_borders();
		block_locations = draw_blocks();
		return;
	}
	if (collision = test_collision(&ball, block_locations, &paddle))
		handle_collision(&ball, &paddle, collision);
	ball.pos.x += ball.vel.x;
	ball.pos.y += ball.vel.y;
	draw_ball(&ball);
	switch (std_button_pressed()) {
		case STD_BUTTON_LEFT:
			paddle.x -= paddle.vel;
			break;
		case STD_BUTTON_RIGHT:
			paddle.x += paddle.vel;
			break;
		default:
			break;
	}
	draw_paddle(&paddle);
}

void main(void)
{
	std_tty_init();
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	std_timer_init();
	app_map_refresh(1);
	while (1) {
		if (std_timer_read(STD_TIMER_0))
			app_map_refresh(0);
	}

	//app_map_draw_blocks();
}
