#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"
#include "app/highscore.h"

#define SPLASH_OFFSET_X 20
#define SPLASH_OFFSET_Y 30

#define DIFFICULTY_OFFSET_X 20
#define DIFFICULTY_OFFSET_Y 30
#define DIFFICULTY_INTERDIST_Y 1
#define DIFFICULTY_TEXT_HEIGHT 6

#define MENU_OFFSET_X 20
#define MENU_OFFSET_Y 30
#define MENU_INTERDIST_Y 1
#define MENU_TEXT_HEIGHT 6

#define RESUME_OFFSET_X 20
#define RESUME_OFFSET_Y 30

#define SAVE_OFFSET_X 20
#define SAVE_OFFSET_Y 30

//! Utility macro for drawing a single line.
/**
 * We do this with a macro because we had memory issues when we didn't.
 */
#define draw_line(string,offset,line) \
do { \
  std_tty_gotoxy(offset,line);\
  std_tty_printf(string);\
} while (0)


//! Draw menu screen
/**
 * @param init Boolean for toggling initializing and redrawing the screen.
 * @param selection A value between 0 and 3 corresponding to game, highscore, resume and exit.
 */
void app_draw_menu(char init, char selection)
{	
	char line = MENU_OFFSET_Y;
	int i;
	static int prior_selection = 3;
	
	if (init)
		std_tty_clrscr();

	if (selection == 0)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);

	if(selection == 0 || prior_selection == 0 || init) {
		draw_line("  _____          __  __ ______ ",MENU_OFFSET_X,line++);
		draw_line(" / ____|   /\\   |  \\/  |  ____|",MENU_OFFSET_X,line++);
		draw_line("| |  __   /  \\  | \\  / | |__   ",MENU_OFFSET_X,line++);
		draw_line("| | |_ | / /\\ \\ | |\\/| |  __|  ",MENU_OFFSET_X,line++);
		draw_line("| |__| |/ ____ \\| |  | | |____ ",MENU_OFFSET_X,line++);
		draw_line(" \\_____/_/    \\_\\_|  |_|______|",MENU_OFFSET_X,line++);
	} else 
		line += MENU_TEXT_HEIGHT;

	for (i = 0; i < MENU_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection == 1)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection == 1 || prior_selection == 1 || init) {
		draw_line(" _    _ _____ _____ _    _  _____  _____ ____  _____  ______  _____ ",MENU_OFFSET_X,line++);
		draw_line("| |  | |_   _/ ____| |  | |/ ____|/ ____/ __ \\|  __ \\|  ____|/ ____|",MENU_OFFSET_X,line++);
		draw_line("| |__| | | || |  __| |__| | (___ | |   | |  | | |__) | |__  | (___  ",MENU_OFFSET_X,line++);
		draw_line("|  __  | | || | |_ |  __  |\\___ \\| |   | |  | |  _  /|  __|  \\___ \\ ",MENU_OFFSET_X,line++);
		draw_line("| |  | |_| || |__| | |  | |____) | |___| |__| | | \\ \\| |____ ____) |",MENU_OFFSET_X,line++);
		draw_line("|_|  |_|_____\\_____|_|  |_|_____/ \\_____\\____/|_|  \\_\\______|_____/ ",MENU_OFFSET_X,line++);
	} else
		line += MENU_TEXT_HEIGHT;

		for (i = 0; i < MENU_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection == 2)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection == 2 || prior_selection == 2 || init) {
		draw_line(" _____  ______  _____ _    _ __  __ ______ ",MENU_OFFSET_X,line++);
		draw_line("|  __ \\|  ____|/ ____| |  | |  \\/  |  ____|",MENU_OFFSET_X,line++);
		draw_line("| |__) | |__  | (___ | |  | | \\  / | |__   ",MENU_OFFSET_X,line++);
		draw_line("|  _  /|  __|  \\___ \\| |  | | |\\/| |  __|  ",MENU_OFFSET_X,line++);
		draw_line("| | \\ \\| |____ ____) | |__| | |  | | |____ ",MENU_OFFSET_X,line++);
		draw_line("|_|  \\_\\______|_____/ \\____/|_|  |_|______|",MENU_OFFSET_X,line++);
	} else
		line += MENU_TEXT_HEIGHT;

	

	for (i = 0; i < MENU_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection == 3)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection == 3 || prior_selection == 3 || init) {
		draw_line(" ________   _______ _______ ",MENU_OFFSET_X,line++);
		draw_line("|  ____\\ \\ / /_   _|__   __|",MENU_OFFSET_X,line++);
		draw_line("| |__   \\ V /  | |    | |   ",MENU_OFFSET_X,line++);
		draw_line("|  __|   > <   | |    | |   ",MENU_OFFSET_X,line++);
		draw_line("| |____ / . \\ _| |_   | |   ",MENU_OFFSET_X,line++);
		draw_line("|______/_/ \\_\\_____|  |_|   ",MENU_OFFSET_X,line++);
	} else
		line += MENU_TEXT_HEIGHT;

	prior_selection = selection;
}

//! Draw splash screen
void app_draw_splash(void) 
{
	int line = SPLASH_OFFSET_Y;

	std_tty_clrscr();
	std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	draw_line("                                                                                                                                            dddddddd",SPLASH_OFFSET_X,line++);
	draw_line("               AAA                                 kkkkkkkk                                                               iiii              d::::::d",SPLASH_OFFSET_X,line++);
	draw_line("              A:::A                                k::::::k                                                              i::::i             d::::::d",SPLASH_OFFSET_X,line++);
	draw_line("             A:::::A                               k::::::k                                                               iiii              d::::::d",SPLASH_OFFSET_X,line++);
	draw_line("            A:::::::A                              k::::::k                                                                                 d:::::d ",SPLASH_OFFSET_X,line++);
	draw_line("           A:::::::::A          rrrrr   rrrrrrrrr   k:::::k    kkkkkkkaaaaaaaaaaaaa  nnnn  nnnnnnnn       ooooooooooo   iiiiiii     ddddddddd:::::d ",SPLASH_OFFSET_X,line++);
	draw_line("          A:::::A:::::A         r::::rrr:::::::::r  k:::::k   k:::::k a::::::::::::a n:::nn::::::::nn   oo:::::::::::oo i:::::i   dd::::::::::::::d ",SPLASH_OFFSET_X,line++);
	draw_line("         A:::::A A:::::A        r:::::::::::::::::r k:::::k  k:::::k  aaaaaaaaa:::::an::::::::::::::nn o:::::::::::::::o i::::i  d::::::::::::::::d ",SPLASH_OFFSET_X,line++);
	draw_line("        A:::::A   A:::::A       rr::::::rrrrr::::::rk:::::k k:::::k            a::::ann:::::::::::::::no:::::ooooo:::::o i::::i d:::::::ddddd:::::d ",SPLASH_OFFSET_X,line++);
	draw_line("       A:::::A     A:::::A       r:::::r     r:::::rk::::::k:::::k      aaaaaaa:::::a  n:::::nnnn:::::no::::o     o::::o i::::i d::::::d    d:::::d ",SPLASH_OFFSET_X,line++);
	draw_line("      A:::::AAAAAAAAA:::::A      r:::::r     rrrrrrrk:::::::::::k     aa::::::::::::a  n::::n    n::::no::::o     o::::o i::::i d:::::d     d:::::d ",SPLASH_OFFSET_X,line++);
	draw_line("     A:::::::::::::::::::::A     r:::::r            k:::::::::::k    a::::aaaa::::::a  n::::n    n::::no::::o     o::::o i::::i d:::::d     d:::::d ",SPLASH_OFFSET_X,line++);
	draw_line("    A:::::AAAAAAAAAAAAA:::::A    r:::::r            k::::::k:::::k  a::::a    a:::::a  n::::n    n::::no::::o     o::::o i::::i d:::::d     d:::::d ",SPLASH_OFFSET_X,line++);
	draw_line("   A:::::A             A:::::A   r:::::r           k::::::k k:::::k a::::a    a:::::a  n::::n    n::::no:::::ooooo:::::oi::::::id::::::ddddd::::::dd",SPLASH_OFFSET_X,line++);
	draw_line("  A:::::A               A:::::A  r:::::r           k::::::k  k:::::ka:::::aaaa::::::a  n::::n    n::::no:::::::::::::::oi::::::i d:::::::::::::::::d",SPLASH_OFFSET_X,line++);
	draw_line(" A:::::A                 A:::::A r:::::r           k::::::k   k:::::ka::::::::::aa:::a n::::n    n::::n oo:::::::::::oo i::::::i  d:::::::::ddd::::d",SPLASH_OFFSET_X,line++);
	draw_line("AAAAAAA                   AAAAAAArrrrrrr           kkkkkkkk    kkkkkkkaaaaaaaaaa  aaaa nnnnnn    nnnnnn   ooooooooooo   iiiiiiii   ddddddddd   ddddd",SPLASH_OFFSET_X,line++);
}

//! Draw highscore screen
void app_draw_highscores(void)
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	app_highscore_render();
}

//! Draw highscore screen
void app_draw_resume(void)
{
	int line = RESUME_OFFSET_Y;

	std_tty_clrscr();
	std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	draw_line("  _   _  ____     _____    __      ________    _____ _______    _______ ______ ",RESUME_OFFSET_X,line++);
	draw_line(" | \\ | |/ __ \\   / ____|  /\\ \\    / /  ____|  / ____|__   __|/\\|__   __|  ____|",RESUME_OFFSET_X,line++);
	draw_line(" |  \\| | |  | | | (___   /  \\ \\  / /| |__    | (___    | |  /  \\  | |  | |__   ",RESUME_OFFSET_X,line++);
	draw_line(" | . ` | |  | |  \\___ \\ / /\\ \\ \\/ / |  __|    \\___ \\   | | / /\\ \\ | |  |  __|  ",RESUME_OFFSET_X,line++);
	draw_line(" | |\\  | |__| |  ____) / ____ \\  /  | |____   ____) |  | |/ ____ \\| |  | |____ ",RESUME_OFFSET_X,line++);
	draw_line(" |_| \\_|\\____/  |_____/_/    \\_\\/   |______| |_____/   |_/_/    \\_\\_|  |______|",RESUME_OFFSET_X,line++);
}

//! Draw difficulties screen
/**
 * @param init Boolean for toggling initializing and redrawing the screen.
 * @param selection A value between 0 and 3 corresponding to easy, normal, hard and very hard.
 */
void app_draw_difficulties(char init, char selection)
{	
	char line = DIFFICULTY_OFFSET_Y;
	int i;
	static int prior_selection = 3;
	
	if (init)
		std_tty_clrscr();

	if (selection == 0)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection == 0 || prior_selection == 0 || init) {
		draw_line(" ______           _______     __",DIFFICULTY_OFFSET_X,line++);
		draw_line("|  ____|   /\\    / ____\\ \\   / /",DIFFICULTY_OFFSET_X,line++);
		draw_line("| |__     /  \\  | (___  \\ \\_/ / ",DIFFICULTY_OFFSET_X,line++);
		draw_line("|  __|   / /\\ \\  \\___ \\  \\   /  ",DIFFICULTY_OFFSET_X,line++);
		draw_line("| |____ / ____ \\ ____) |  | |  ",DIFFICULTY_OFFSET_X,line++);
		draw_line("|______/_/    \\_\\_____/   |_|   ",DIFFICULTY_OFFSET_X,line++);
	} else
		line += DIFFICULTY_TEXT_HEIGHT;

	for (i = 0; i < DIFFICULTY_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection == 1)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection == 1 || prior_selection == 1 || init) {
		draw_line(" _   _  ____  _____  __  __          _    ",DIFFICULTY_OFFSET_X,line++);
		draw_line("| \\ | |/ __ \\|  __ \\|  \\/  |   /\\   | |     ",DIFFICULTY_OFFSET_X,line++);
		draw_line("|  \\| | |  | | |__) | \\  / |  /  \\  | |     ",DIFFICULTY_OFFSET_X,line++);
		draw_line("| . ` | |  | |  _  /| |\\/| | / /\\ \\ | |     ",DIFFICULTY_OFFSET_X,line++);
		draw_line("| |\\  | |__| | | \\ \\| |  | |/ ____ \\| |____ ",DIFFICULTY_OFFSET_X,line++);
		draw_line("|_| \\_|\\____/|_|  \\_\\_|  |_/_/    \\_\\______|",DIFFICULTY_OFFSET_X,line++);
	} else
		line += DIFFICULTY_TEXT_HEIGHT;

	for (i = 0; i < DIFFICULTY_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection == 2)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection == 2 || prior_selection == 2 || init) {
		draw_line(" _    _          _____  _____  ",DIFFICULTY_OFFSET_X,line++);
		draw_line("| |  | |   /\\   |  __ \\|  __ \\ ",DIFFICULTY_OFFSET_X,line++);
		draw_line("| |__| |  /  \\  | |__) | |  | |",DIFFICULTY_OFFSET_X,line++);
		draw_line("|  __  | / /\\ \\ |  _  /| |  | |",DIFFICULTY_OFFSET_X,line++);
		draw_line("| |  | |/ ____ \\| | \\ \\| |__| |",DIFFICULTY_OFFSET_X,line++);
		draw_line("|_|  |_/_/    \\_\\_|  \\_\\_____/ ",DIFFICULTY_OFFSET_X,line++);
	} else
		line += DIFFICULTY_TEXT_HEIGHT;

	for (i = 0; i < DIFFICULTY_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection == 3)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection == 3 || prior_selection == 3 || init) {
		draw_line("__      ________ _______     __  _    _          _____  _____  ",DIFFICULTY_OFFSET_X,line++);
		draw_line("\\ \\    / /  ____|  __ \\ \\   / / | |  | |   /\\   |  __ \\|  __ \\ ",DIFFICULTY_OFFSET_X,line++);
		draw_line(" \\ \\  / /| |__  | |__) \\ \\_/ /  | |__| |  /  \\  | |__) | |  | |",DIFFICULTY_OFFSET_X,line++);
		draw_line("  \\ \\/ / |  __| |  _  / \\   /   |  __  | / /\\ \\ |  _  /| |  | |",DIFFICULTY_OFFSET_X,line++);
		draw_line("   \\  /  | |____| | \\ \\  | |    | |  | |/ ____ \\| | \\ \\| |__| |",DIFFICULTY_OFFSET_X,line++);
		draw_line("    \\/   |______|_|  \\_\\ |_|    |_|  |_/_/    \\_\\_|  \\_\\_____/ ",DIFFICULTY_OFFSET_X,line++);
	} else
		line += DIFFICULTY_TEXT_HEIGHT;

	prior_selection = selection;
}


//! Draw save animation
void app_draw_save(void)
{
	int line = SAVE_OFFSET_Y;

	std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	draw_line("  _____    __      ________ _____  ",SAVE_OFFSET_X,line++);
	draw_line(" / ____|  /\\ \\    / /  ____|  __ \\ ",SAVE_OFFSET_X,line++);
	draw_line("| (___   /  \\ \\  / /| |__  | |  | |",SAVE_OFFSET_X,line++);
	draw_line(" \\___ \\ / /\\ \\ \\/ / |  __| | |  | |",SAVE_OFFSET_X,line++);
	draw_line(" ____) / ____ \\  /  | |____| |__| |",SAVE_OFFSET_X,line++);
	draw_line("|_____/_/    \\_\\/   |______|_____/ ",SAVE_OFFSET_X,line++);

	line = SAVE_OFFSET_Y;

	// draw blanks on top for animation effect
	draw_line("                                   ",SAVE_OFFSET_X,line++);
	draw_line("                                   ",SAVE_OFFSET_X,line++);
	draw_line("                                   ",SAVE_OFFSET_X,line++);
	draw_line("                                   ",SAVE_OFFSET_X,line++);
	draw_line("                                   ",SAVE_OFFSET_X,line++);
	draw_line("                                   ",SAVE_OFFSET_X,line++);

}

//! Draw end game screen
void app_draw_endgame()
{
	std_tty_clrscr();
	std_tty_gotoxy(5,2);
	std_tty_printf("Game Over");
}
