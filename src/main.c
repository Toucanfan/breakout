#include "app/draw.h"
#include "std/draw.h"
#include "std/button.h"

static enum State game_state;
static char difficulty;

void initialization(void);
void menu_screen(void);

enum State {
   IN_SPLASH,
   IN_MENU,
   IN_GAME,
   IN_HIGHSCORE_SCREEN,
   IN_HELP_SCREEN,
   IN_DIFFICULTY_SELECT,
};

void main()
{
enum State game_state;
unsigned char cur_diff;

init_splash();

while (true) {
	switch(game_state){
		case IN_SPLASH:
			splash_screen();
			break;
		case IN_GAME:
			...
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
			dif_select_screen();
			break:
		default:
			init_splash();
	}
}
		
		
		
}

void init_menu ()
{
	app_draw_difficulties(GAME);
	State = IN_MENU;
}
	
void menu_screen(void)
{
	static unsigned char menu_selection = GAME;
	
	while (std_button_new_press() == STD_BUTTON_NONE) {}	
	switch(std_button_press)()) {
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
				case GAME: init_dif_select(); 
					break;
				case HELP: init_help();
					break;
				case HIGHSCORES: init_highscores();
					break;
				case EXIT: init_splash(); 
					break;
				default:
			}
		default:
	}
}	
	
void init_dif_select 
{
app_draw_difficulties(NORMAL);
State = IN_DIFFICULTY_SELECT;
}

void dif_select_screen(void)
{
	static char cur_diff_selection = NORMAL;
	
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	switch(std_button_press()) {
		case STD_BUTTON_LEFT:
			cur_diff = --cur_diff_selection & 0x03;
			app_draw_difficulties(cur_diff_selection);
			break;
		case STD_BUTTON_RIGHT:
			cur_diff = ++cur_diff_selection & 0x03;
			app_draw_difficulties(cur_diff_selection);
			break;
		case STD_BUTTON_MIDDLE:
			difficulty = cur_diff_selection;
			init_game();
			break:
		default:
	}	
}

void init_highscores(void) 
{
	app_draw_highscores();
	State = IN_HIGHSCORE_SCREEN;
}
	
void highscore_screen(void) 
{
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	init_menu();
}


void init_help(void) 
{
	app_draw_help();
	State = IN_HELP_SCREEN;
}
	
void help_screen(void) 
{
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	init_menu();
}


void init_splash(void) 
{
	app_draw_splash();
	State = IN_SPLASH;
}

void splash_screen(void)
{
	while (std_button_new_press() == STD_BUTTON_NONE) {}
	init_menu();
}