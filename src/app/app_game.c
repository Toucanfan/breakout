#include "std/draw.h"
#include "std/tty.h"
#include "std/fixpt.h"
#include "std/ti.h"

#include "app/draw.h"
#include "app/game.h"
#include "app/map.h"
#include "app/screen.h"
#include "app/highscore.h"

//! Updates game states
/**
 * Calls app_map_refresh to update map state and moves to next level or ends game.
 *
 * @param ctx The game context
 */
void app_game_tick(struct app_map_context *ctx, char *next_screen)
{
	app_map_refresh(ctx);
	
	if (ctx->blocks_left == 0) {
		ctx->level++;
		ctx->score += ctx->difficulty * 20;  // bonus points for level finish
		app_map_reset(ctx);
	}
	
	if (ctx->lives == 0) {
		app_game_end(ctx, next_screen); //  HENRIKS FUNKTION OM HIGHSCORE
	}
}



void app_game_end(struct app_map_context *ctx, char *next_screen)
{
	struct app_highscore new_highscore;
	struct std_draw_point point;
	char name[4];
	name[0] = ' ';
	name[1] = ' ';
	name[2] = ' ';
	name[3] = '\0';
	if(app_highscore_test(ctx->score)) {
		app_draw_endgame();
		new_highscore.score = ctx->score;
		point.x = 9;
		point.y = 3;

		std_tty_gotoxy(3, 3);
		std_tty_printf("Name:");

		std_ti_create(&point, name, 4, &std_ti_letters_test);

		new_highscore.name[0] = name[0];
		new_highscore.name[1] = name[1];
		new_highscore.name[2] = name[2];
		new_highscore.name[3] = name[3];

		app_highscore_add(new_highscore);
	}
	*next_screen = APP_SCREEN_HIGHSCORE;
}
