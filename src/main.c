#include <string.h>

#include "app/draw.h"
#include "app/highscore.h"
#include "app/game.h"
#include "app/menu.h"
#include "app/screen.h"

#include "std/draw.h"
#include "std/ti.h"
#include "std/button.h"
#include "std/fixpt.h"
#include "std/timer.h"
#include "std/led.h"
#include "std/rom.h"


static void enter_diff_select_screen(struct app_map_context *ctx, char *next_screen)
{
	static char cur_diff_selection = MEDIUM;

	app_draw_difficulties(1,MEDIUM);
	
	while (1) {
		while (std_button_new_press() == STD_BUTTON_NONE) {}
		switch(std_button_pressed()) {
		case STD_BUTTON_LEFT:
			cur_diff_selection = --cur_diff_selection & 0x03;
			app_draw_difficulties(0,cur_diff_selection);
			break;
		case STD_BUTTON_RIGHT:
			cur_diff_selection = ++cur_diff_selection & 0x03;
			app_draw_difficulties(0,cur_diff_selection);
			break;
		case STD_BUTTON_MIDDLE:
			ctx->difficulty = cur_diff_selection + 1;  // Allows difficulty to be used as a multiplier
			*next_screen = APP_SCREEN_GAME;
			return;
			break;
		default:
			break;
		}	
	}
}

	
static void enter_highscores_screen(char *next_screen) 
{
	app_draw_highscores();
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	*next_screen = APP_SCREEN_MENU;
}



static void enter_splash_screen(char *next_screen)
{
	app_draw_splash();
	std_led_set_string("Arkanoid    ");
	while (std_button_new_press() == STD_BUTTON_NONE) {
		std_led_refresh();
		}
	*next_screen = APP_SCREEN_MENU;
}

static void enter_resume_screen(struct app_map_context *ctx, char *next_screen) 
{
 	std_rom_read(STD_ROM_PAGE1, ctx, sizeof(*ctx));
	if (ctx->resumed_game == 1) {    // 99% of the time, this will not be the case if no save is present
		*next_screen = APP_SCREEN_GAME;
		return;
	}

	app_draw_resume();
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	*next_screen = APP_SCREEN_MENU;
}

static void enter_menu_screen(struct app_map_context *ctx, char *next_screen)
{
	app_menu_loop(ctx, next_screen);
}

static void enter_game_screen(struct app_map_context *ctx, char *next_screen)
{
	char next_screen_save = *next_screen;

	if (ctx->resumed_game != 1) {
		ctx->level = 1;
		ctx->score = 0;
		ctx->lives = 3;
	}
	
	app_map_reset(ctx);

	while (*next_screen == next_screen_save) {
		if (std_timer_read(STD_TIMER_0))
			app_game_tick(ctx, next_screen);
	}
}



void main(void)
{
	struct app_map_context ctx;
	char next_screen = APP_SCREEN_SPLASH;
	
	ctx.resumed_game = 0;
	std_tty_init();
	std_tty_clrscr();
	std_timer_configure(STD_TIMER_0, 75);
	std_timer_start(STD_TIMER_0);
	std_led_init();
	app_highscore_init(); // related to setting up highscores, not game_state
	while (1) {
		switch(next_screen) {
			case APP_SCREEN_GAME:
				enter_game_screen(&ctx, &next_screen);
				break;
			case APP_SCREEN_MENU:
				enter_menu_screen(&ctx, &next_screen);
				break;
			case APP_SCREEN_RESUME:
				enter_resume_screen(&ctx, &next_screen);
				break;
			case APP_SCREEN_HIGHSCORE:
				enter_highscores_screen(&next_screen);
				break;
			case APP_SCREEN_DIFFICULTY_SELECT:
				enter_diff_select_screen(&ctx, &next_screen);
				break;
			default:
			case APP_SCREEN_SPLASH:
				enter_splash_screen(&next_screen);
				break;
		}
	}
}

