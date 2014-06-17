#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"
#include "std/timer.h"
#include "std/button.h"

extern long *draw_blocks(void);
extern char test_blck_collision(struct ball *ball, long *block_locations);

#define WIDTH 170
#define HEIGHT 60
#define RBORDER std_fixpt_i2f(WIDTH-4)
#define BBORDER std_fixpt_i2f(HEIGHT-2)
#define TBORDER std_fixpt_i2f(3)
#define LBORDER std_fixpt_i2f(4)

#define COLLISION_NONE 0x0
#define COLLISION_HORIZONTAL 0x1
#define COLLISION_VERTICAL 0x2

static struct ball {
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
};

static struct paddle {
	long x_left;
	long vel;
}

static void draw_borders(void)
{
	struct std_draw_box topb;
	struct std_draw_box leftb;
	struct std_draw_box rightb;

	topb.tl.x = 1;
	topb.tl.y = 1;
	topb.br.x = WIDTH;
	topb.br.y = 1;
	topb.color = STD_TTY_BCOLOR_GRAY;

	leftb.tl.x = 1;
	leftb.tl.y = 1;
	leftb.br.x = 2;
	leftb.br.y = HEIGHT;
	leftb.color = STD_TTY_BCOLOR_GRAY;

	rightb.tl.x = WIDTH-1;
	rightb.tl.y = 1;
	rightb.br.x = WIDTH;
	rightb.br.y = HEIGHT;
	rightb.color = STD_TTY_BCOLOR_GRAY;

	std_draw_box(&leftb);
	std_draw_box(&topb);
	std_draw_box(&rightb);
}

static void draw_ball(struct ball *ball)
{
	static int x_old = 6;
	static int y_old = 6;
	int x, y;
	
	x = std_fixpt_f2i(ball->pos.x);
	y = std_fixpt_f2i(ball->pos.y);

	if (x != x_old && y != y_old) {
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
	static int x_old = WIDTH/2;
	int x;
	struct std_draw_box box;

	x = std_fixpt_f2i(paddle->x_left);

	if (x != x_old) {
		/* remove drawing of last paddle */
		box.color = STD_TTY_BCOLOR_BLACK;
		std_draw_box(&box);
	
		/* draw paddle at new position */
		box.tl.x = x;
		box.tl.y = HEIGHT;
		box.br.x = x+7;
		box.br.y = HEIGHT;
		box.color = STD_TTY_BCOLOR_GRAY;
		std_draw_box(&box);

		x_old = x;
	}
}

static char test_collision(struct ball *ball, long *block_locations)
{
	char r;

	if (ball->pos.x < LBORDER)
		return COLLISION_VERTICAL;

	else if (ball->pos.x > RBORDER)
		return COLISION_VERTICAL;

	else if (r = test_block_collision(ball, block_locations))
		return r;

	else if (ball->pos.y < TBORDER)
		return COLLISION_HORIZONTAL;

	else if (ball->pos.y > BBORDER)
		return COLLISION_HORIZONTAL;

	else 
		return COLLISION_NONE;
}

static void handle_collision(struct ball *ball, char coll_type)
{
	switch(coll_type) {
	case COLLISION_VERTICAL:
		ball->vel.x = -(ball->vel.x);
		break;
	case COLLISION_HORIZONTAL:
		ball->vel.y = -(ball->vel.y);
		break;
	default:
	case COLLISION_NONE:
		break;
	}
}

void app_map_refresh(char should_reset)
{
	static struct ball ball;
	static struct paddle paddle;
	static long *block_locations;
	char collision;
	if (should_reset) {
		ball.pos.x = std_fixpt_i2f(WIDTH/2);
		ball.pos.y = std_fixpt_i2f(HEIGHT-3);
		ball.vel.x = std_fixpt_div(std_fixpt_i2f(-1), std_fixpt_i2f(50));
		ball.vel.y = std_fixpt_div(std_fixpt_i2f(-1), std_fixpt_i2f(50));
		paddle.x_left = std_fixpt_i2f(WIDTH/2-3);
		paddle.vel = std_fixpt_i2f(1);
		std_tty_clrscr();
		draw_borders();
		block_locations = draw_blocks();
		return;
	}
	draw_paddle(&paddle);
	draw_ball(&ball);
	collision = test_collision(&ball, block_locations);
	handle_collision(&ball, collision);

	if (std_button_pressed(STD_BUTTON_LEFT))
		paddle.x_left -= paddle.vel;
	else if (std_button_pressed(STD_BUTTON_RIGHT))
		paddle.x_right += paddle.vel;

	ball.pos.x += ball.vel.x;
	ball.pos.y += ball.vel.y;
}

void main(void)
{
	std_tty_init();
	std_tty_clrscr();
	std_timer_init();
	app_map_refresh(1);
	while (1) {
		if (std_timer_read(STD_TIMER_0))
			app_map_refresh(0);
	}

	//app_map_draw_blocks();
}
