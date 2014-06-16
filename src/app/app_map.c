#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"

extern void app_map_draw_blocks(void);

#define WIDTH 170
#define HEIGHT 60
#define FIXPT_WIDTH std_fixpt_i2f(WIDTH-4)
#define FIXPT_HEIGHT std_fixpt_i2f(HEIGHT-2)
#define FIXPT_ORIGIN_Y std_fixpt_i2f(3)
#define FIXPT_ORIGIN_X std_fixpt_i2f(4)

#define COLLISION_NONE 0x0
#define COLLISION_LBORDER 0x1
#define COLLISION_RBORDER 0x2
#define COLLISION_TBORDER 0x3
#define COLLISION_PADDLE 0x4

static struct ball {
	struct std_fixpt_point pos;
	struct std_fixpt_point vel;
};

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
		/* remove drawing of last box */
		std_tty_gotoxy(x_old, y_old);
		std_tty_set_fcolor(STD_TTY_FCOLOR_BLACK);
		std_tty_printf("o");
	
		/* draw box at new ball position */
		std_tty_gotoxy(x, y);
		std_tty_set_fcolor(STD_TTY_FCOLOR_WHITE);
		std_tty_printf("o");

		x_old = x;
		y_old = y;
	}
}

static char test_collision(struct ball *ball)
{
	if (ball->pos.x < FIXPT_ORIGIN_X)
		return COLLISION_LBORDER;

	else if (ball->pos.x > FIXPT_WIDTH)
		return COLLISION_RBORDER;

	else if (ball->pos.y < FIXPT_ORIGIN_Y)
		return COLLISION_TBORDER;

	else if (ball->pos.y > FIXPT_HEIGHT)
		return COLLISION_PADDLE;

	else 
		return COLLISION_NONE;
}

static void handle_collision(struct ball *ball, char coll_type)
{
	switch(coll_type) {
	case COLLISION_LBORDER:
		ball->vel.x = -(ball->vel.x);
		break;
	case COLLISION_RBORDER:
		ball->vel.x = -(ball->vel.x);
		break;
	case COLLISION_TBORDER:
		ball->vel.y = -(ball->vel.y);
		break;
	case COLLISION_PADDLE:
		ball->vel.y = -(ball->vel.y);
		break;
	default:
	case COLLISION_NONE:
		break;
	}
}

void app_map_refresh(void)
{
	static int times_called = 0;
	static struct ball ball;
	char collision;
	if (!times_called) {
		ball.pos.x = std_fixpt_i2f(WIDTH/2);
		ball.pos.y = std_fixpt_i2f(HEIGHT-3);
		ball.vel.x = std_fixpt_div(std_fixpt_i2f(-1), std_fixpt_i2f(50));
		ball.vel.y = std_fixpt_div(std_fixpt_i2f(-1), std_fixpt_i2f(50));
		std_tty_clrscr();
		draw_borders();
	}
	draw_ball(&ball);
	collision = test_collision(&ball);
	handle_collision(&ball, collision);
	ball.pos.x += ball.vel.x;
	ball.pos.y += ball.vel.y;
	times_called++;
}

void main(void)
{
	std_tty_init();
	std_tty_clrscr();
	/*
	while (1) {
		app_map_refresh();
	}
	*/
	draw_borders();
	app_map_draw_blocks();
	while (1);
}
