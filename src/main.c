#include "app/draw.h"
#include "app/highscore.h"
#include "app/map.h"
#include "std/draw.h"
#include "std/text_input.h"
#include "std/button.h"
#include "std/fixpt.h"

#define IN_SPLASH 0
#define IN_GAME 1
#define IN_HELP_SCREEN 2
#define IN_HIGHSCORE_SCREEN 3
#define IN_MENU 4
#define IN_DIFFICULTY_SELECT 5


static char game_state;

void main(void);
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

struct game_condition {
	char difficulty;
	char level;
	char lives;
	struct app_map_ball ball;
	struct app_map_paddle paddle;
	long *blocks;
	int blocks_left;
}

void main(void)
{
	struct game_condition game_condition;
	
	std_tty_init();
	std_tty_clrscr();
	init_splash();
	while (1) {
		switch(game_state){
			case IN_SPLASH:
				splash_screen();
				break;
			case IN_GAME:
				game_tick(&game_condition);
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
				diff_select_screen(&game_condition);
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

void diff_select_screen(struct game_condition *game_condition)
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
			game_condition->difficulty = cur_diff_selection;
			init_game(game_condition);
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

void init_endgame(char score)
{
	struct app_highscore new_highscore;
	struct std_draw_point point;
	char name[4];
	if(app_highscore_test(score)) {
		new_highscore.score = score;
		point.x = 3;
		point.y = 3;

		std_text_input_create(&point, name, 4, &std_ti_letters_test)

		new_highscore.name = name;

		app_add_highscore(new_highscore);
	}
	init_highscores();
}

void init_game(struct game_condition *game_condition) {
	game_condition->level = 1;
	game_condition->score = 0;
	game_condition->lives = 3;
	init_level(game_condition);
	game_state = IN_GAME
}

void init_level(struct game_condition *game_condition) {
	draw_blocks(game_condition);
	game_condition->ball.vel.x = std_fixpt_i2f(1)/32;
	game_condition->ball.vel.y = -std_fixpt_i2f(1)/32;
	game_condition->ball.pos.x = 30;
	game_condition->ball.pos.y = 30;
	game_condition->paddle.x = 30;
	game_condition->paddle.vel = 1;
}