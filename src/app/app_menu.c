#include "std/tty.h"
#include "std/button.h"
#include "std/tty.h"
#include "std/led.h"
#include "app/menu.h"
#include "app/highscore.h"
#include "app/draw.h"
#include "app/screen.h"

#define GAME 0
#define HIGHSCORES 1
#define RESUME 2
#define EXIT 3

void app_menu_loop(struct app_map_context *ctx, char *next_screen)
{
	static unsigned char menu_selection = GAME;
	static char hstring[32];
	struct app_highscore *highscore = app_highscore_get_topscore();
	app_draw_menu(1, menu_selection);
	std_tty_sprintf(hstring, "Topscore: %s:%d    ", highscore->name, highscore->score);
	std_led_set_string(hstring);
	while (1) {
		while (std_button_new_press() == STD_BUTTON_NONE) {
			std_led_refresh();
		}
		switch(std_button_pressed()) {
		case STD_BUTTON_LEFT:
			menu_selection = --menu_selection & 0x03;
			app_draw_menu(0,menu_selection);
			break;
		case STD_BUTTON_RIGHT:
			menu_selection = ++menu_selection & 0x03;
			app_draw_menu(0,menu_selection);
			break;
		case STD_BUTTON_MIDDLE:
			switch (menu_selection) {
				case GAME: 
					*next_screen = APP_SCREEN_DIFFICULTY_SELECT;
					break;
				case RESUME:
					*next_screen = APP_SCREEN_RESUME;
					break;
				case HIGHSCORES:
					*next_screen = APP_SCREEN_HIGHSCORE;
					break;
				case EXIT:
					*next_screen = APP_SCREEN_SPLASH;
					break;
				default:
					break;
			}
			menu_selection = GAME; // default selection for next time
			return;
		break;
		default:
			break;
		}
	}
}	
