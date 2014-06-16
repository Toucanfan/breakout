#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"

#define WIDTH 150
#define HEIGHT 30
#define FIXPT_WIDTH std_fixpt_i2f(WIDTH)
#define FIXPT_HEIGHT std_fixpt_i2f(HEIGHT)

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

	topb.tl.x = 0;
	topb.tl.y = 0;
	topb.br.x = WIDTH;
	topb.br.y = 0;
	topb.color = STD_TTY_BCOLOR_GRAY;

	leftb.tl.x = 0;
	leftb.tl.y = 0;
	leftb.br.x = 2;
	leftb.br.y = HEIGHT;
	leftb.color = STD_TTY_BCOLOR_GRAY;

	rightb.tl.x = WIDTH-1;
	rightb.tl.y = 0;
	rightb.br.x = WIDTH;
	rightb.br.y = HEIGHT;
	rightb.color = STD_TTY_BCOLOR_GRAY;

	std_draw_box(&leftb);
	std_draw_box(&topb);
	std_draw_box(&rightb);
}

static void draw_ball(struct ball *ball)
{
	static struct std_draw_box box = {
		{4, 5},
		{4, 5}, 
		STD_TTY_BCOLOR_GRAY
	};

	/* remove drawing of last box */
	box.color = STD_TTY_BCOLOR_BLACK;
	std_draw_box(&box);

	/* draw box at new ball position */
	box.tl.x = std_fixpt_f2i(ball->pos.x);
	box.br.x = std_fixpt_f2i(ball->pos.x);
	box.tl.y = std_fixpt_f2i(ball->pos.y);
	box.br.y = std_fixpt_f2i(ball->pos.y);
	box.color = STD_TTY_BCOLOR_GRAY;
	std_draw_box(&box);
}

static char test_collision(struct ball *ball)
{
	if (ball->pos.x < 0)
		return COLLISION_LBORDER;

	else if (ball->pos.x > FIXPT_WIDTH)
		return COLLISION_RBORDER;

	else if (ball->pos.y < 0)
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
		ball->pos.x = 0;
		ball->vel.x = -(ball->vel.x);
		break;
	case COLLISION_RBORDER:
		ball->pos.x = FIXPT_WIDTH;
		ball->vel.x = -(ball->vel.x);
		break;
	case COLLISION_TBORDER:
		ball->pos.y = 0;
		ball->vel.y = -(ball->vel.y);
		break;
	case COLLISION_PADDLE:
		ball->pos.y = FIXPT_HEIGHT;
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
		ball.pos.y = std_fixpt_i2f(HEIGHT-2);
		ball.vel.x = std_fixpt_i2f(1);
		ball.vel.y = std_fixpt_i2f(1);
		std_tty_clrscr();
		draw_borders();
	}
	draw_ball(&ball);
	ball.pos.x += ball.vel.x;
	ball.pos.y += ball.vel.y;
	//collision = test_collision(&ball);
	//handle_collision(&ball, collision);
	times_called++;
}

void main(void)
{
	int i, j;
	std_tty_init();	
	/*
	while (1) {
		app_map_refresh();
	}
	*/
	i = std_fixpt_i2f(1);
	j = std_fixpt_i2f(1);
	std_tty_gotoxy(0,0);
	std_tty_printf("%d", std_fixpt_f2i(i+j));
}
