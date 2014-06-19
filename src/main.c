#include "app/draw.h"
#include "app/highscore.h"
#include "std/draw.h"
#include "std/text_input.h"
#include "std/button.h"
#include "std/fixpt.h"
#include "std/timer.h"
#include "app/game.h"
#include "app/state.h"


void init_splash(void);
void init_menu(void);
void init_diff_select(void);
void diff_select_screen(void);
void init_highscores(void);
void menu_screen(void);
void highscores_screen(void);
void init_help(void);
void help_screen(void);
void init_splash(void);
void splash_screen(void);

char game_state;

void main(void)
{
	struct app_map_context ctx;
	
	std_tty_init();
	std_tty_clrscr();
	std_timer_init();
	init_splash();
	while (1) {
		switch(game_state){
			case IN_SPLASH:
				splash_screen();
				break;
			case IN_GAME:
				if (std_timer_read(STD_TIMER_0))
					game_tick(&ctx);
				break;
			case IN_MENU:
				menu_screen();
				break;
			case IN_HELP_SCREEN:
				help_screen();
				break;
			case IN_HIGHSCORE_SCREEN:
				highscores_screen();
				break;
			case IN_DIFFICULTY_SELECT:
				diff_select_screen(&ctx);
				break;
			default:
				init_splash();
		}
	}
}

void init_menu(void)
{
	app_draw_menu(GAME);
	game_state = IN_MENU;
}
	
void menu_screen(void)
{
	static unsigned char menu_selection = GAME;
	
	while (std_button_new_press() == STD_BUTTON_NONE) {}	
	switch(std_button_pressed()) {
		case STD_BUTTON_LEFT:
			menu_selection = --menu_selection & 0x03;
			app_draw_menu(menu_selection);
			break;
		case STD_BUTTON_RIGHT:
			menu_selection = ++menu_selection & 0x03;
			app_draw_menu(menu_selection);
			break;
		case STD_BUTTON_MIDDLE:
			switch (menu_selection) {
				case GAME: 
					init_diff_select(); 
					break;
				case HELP:
					init_help();
					break;
				case HIGHSCORES:
					init_highscores();
					break;
				case EXIT:
					init_splash(); 
					break;
				default:
					break;
			}
	    	break;
	 	default:
			break;
	}
}	
	
void init_diff_select(void)
{
app_draw_difficulties(MEDIUM);
game_state = IN_DIFFICULTY_SELECT;
}

void diff_select_screen(struct app_map_context *ctx)
{
	static char cur_diff_selection = MEDIUM;
	
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	switch(std_button_pressed()) {
		case STD_BUTTON_LEFT:
			cur_diff_selection = --cur_diff_selection & 0x03;
			app_draw_difficulties(cur_diff_selection);
			break;
		case STD_BUTTON_RIGHT:
			cur_diff_selection = ++cur_diff_selection & 0x03;
			app_draw_difficulties(cur_diff_selection);
			break;
		case STD_BUTTON_MIDDLE:
			ctx->difficulty = cur_diff_selection + 1;  // Allows difficulty to be used as a multiplier
			init_game(ctx);
			break;
		default:
			break;
	}	
}

void init_highscores(void) 
{
	app_draw_highscores();
	game_state = IN_HIGHSCORE_SCREEN;
}
	
void highscores_screen(void) 
{
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	init_menu();
}


void init_help(void) 
{
	app_draw_help();
	game_state = IN_HELP_SCREEN;
}
	
void help_screen(void) 
{
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	init_menu();
}


void init_splash(void) 
{
	app_draw_splash();
	game_state = IN_SPLASH;
}

void splash_screen(void)
{
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	init_menu();
}

void init_endgame(struct app_map_context *ctx)
{
	struct app_highscore new_highscore;
	struct std_draw_point point;
	char name[4];
	if(app_highscore_test(ctx->score)) {
		new_highscore.score = ctx->score;
		point.x = 3;
		point.y = 3;

		std_text_input_create(&point, name, 4, &std_ti_letters_test);

		new_highscore.name = name;

		app_add_highscore(new_highscore);
	}
	init_highscores();
}

