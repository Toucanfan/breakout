#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"
#include "std/fixpt.h"
#include "app/game.h"
#include "app/map.h"
#include "app/state.h"

void game_tick (struct app_map_context *ctx)
{
	app_map_refresh(ctx);
	
	if (ctx->blocks_left == 0) {
		ctx->level++;
		ctx->score += ctx->difficulty * 20;  // bonus points for level finish
		app_map_reset(ctx);
	}
	
	if (ctx->lives == 0) {
		init_endgame(ctx); //  HENRIKS FUNKTION OM HIGHSCORE
		std_tty_gotoxy(5,5);
		std_tty_printf("troels");
	}
}

void init_game(struct app_map_context *ctx) {
	ctx->level = 1;
	ctx->score = 0;
	ctx->lives = 3;
	
	app_map_reset(ctx);
	game_state = IN_GAME;
}

