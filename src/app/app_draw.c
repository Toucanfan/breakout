#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"
#include "app/highscore.h"

#define SPLASH_OFFSET_X 20
#define SPLASH_OFFSET_Y 30
#define SPLASH_ROWS 17

#define DIFFICULTY_OFFSET_X 20
#define DIFFICULTY_OFFSET_Y 30
#define DIFFICULTY_ROWS 17
#define DIFFICULTY_INTERDIST_Y 1
#define DIFFICULTY_AMOUNT 4
#define draw_line(string,offset,line) \
do { \
  std_tty_gotoxy(offset,line);\
  std_tty_printf(string);\
} while (0)

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

void app_draw_highscores(void)
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	app_render_highscore();
}


void app_draw_difficulties(char selection)
{	
	char init = 1; 
	char line = DIFFICULTY_OFFSET_Y;
	int i;
	static int prior_selection = 3;

	if (selection)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection || prior_selection || init) {
		draw_line(" ______           _______     __",DIFFICULTY_OFFSET_X,line++)
		draw_line("|  ____|   /\\    / ____\\ \\   / /",DIFFICULTY_OFFSET_X,line++)
		draw_line("| |__     /  \\  | (___  \\ \\_/ / ",DIFFICULTY_OFFSET_X,line++)
		draw_line("|  __|   / /\\ \\  \\___ \\  \\   /  ",DIFFICULTY_OFFSET_X,line++)
		draw_line("| |____ / ____ \\ ____) |  | |  ",DIFFICULTY_OFFSET_X,line++)
		draw_line("|______/_/    \\_\\_____/   |_|   ",DIFFICULTY_OFFSET_X,line++)
	}

	for (i = 0; i < DIFFICULTY_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection || prior_selection || init) {
		draw_line(" _   _  ____  _____  __  __          _    ",DIFFICULTY_OFFSET_X,line++)
		draw_line("| \\ | |/ __ \\|  __ \\|  \\/  |   /\\   | |     ",DIFFICULTY_OFFSET_X,line++)
		draw_line("|  \\| | |  | | |__) | \\  / |  /  \\  | |     ",DIFFICULTY_OFFSET_X,line++)
		draw_line("| . ` | |  | |  _  /| |\\/| | / /\\ \\ | |     ",DIFFICULTY_OFFSET_X,line++)
		draw_line("| |\\  | |__| | | \\ \\| |  | |/ ____ \\| |____ ",DIFFICULTY_OFFSET_X,line++)
		draw_line("|_| \\_|\\____/|_|  \\_\\_|  |_/_/    \\_\\______|",DIFFICULTY_OFFSET_X,line++)
	}

	for (i = 0; i < DIFFICULTY_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection || prior_selection || init) {
		draw_line(" _    _          _____  _____  ",DIFFICULTY_OFFSET_X,line++)
		draw_line("| |  | |   /\\   |  __ \\|  __ \\ ",DIFFICULTY_OFFSET_X,line++)
		draw_line("| |__| |  /  \\  | |__) | |  | |",DIFFICULTY_OFFSET_X,line++)
		draw_line("|  __  | / /\\ \\ |  _  /| |  | |",DIFFICULTY_OFFSET_X,line++)
		draw_line("| |  | |/ ____ \\| | \\ \\| |__| |",DIFFICULTY_OFFSET_X,line++)
		draw_line("|_|  |_/_/    \\_\\_|  \\_\\_____/ ",DIFFICULTY_OFFSET_X,line++)
	}

	for (i = 0; i < DIFFICULTY_INTERDIST_Y; i++)
		std_tty_printf("\n");

	if (selection)
		std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	else
		std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	if(selection || prior_selection || init) {
		draw_line("__      ________ _______     __  _    _          _____  _____  ",DIFFICULTY_OFFSET_X,line++)
		draw_line("\\ \\    / /  ____|  __ \\ \\   / / | |  | |   /\\   |  __ \\|  __ \\ ",DIFFICULTY_OFFSET_X,line++)
		draw_line(" \\ \\  / /| |__  | |__) \\ \\_/ /  | |__| |  /  \\  | |__) | |  | |",DIFFICULTY_OFFSET_X,line++)
		draw_line("  \\ \\/ / |  __| |  _  / \\   /   |  __  | / /\\ \\ |  _  /| |  | |",DIFFICULTY_OFFSET_X,line++)
		draw_line("   \\  /  | |____| | \\ \\  | |    | |  | |/ ____ \\| | \\ \\| |__| |",DIFFICULTY_OFFSET_X,line++)
		draw_line("    \\/   |______|_|  \\_\\ |_|    |_|  |_/_/    \\_\\_|  \\_\\_____/ ",DIFFICULTY_OFFSET_X,line++)
	}
}

void app_draw_help(void)
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	std_tty_printf("help yo motherfucker");
}

void app_draw_menu(char selection)
{
	std_tty_clrscr();
	std_tty_gotoxy(5,2);
	std_tty_printf("EAZEY");
	std_tty_gotoxy(5,3);
	std_tty_printf("mediocre");
	std_tty_gotoxy(5,4);
	std_tty_printf("hard ass nigger");
	std_tty_gotoxy(5,5);
	std_tty_printf("lolisaurus");
	
	std_tty_gotoxy(3,selection+2);
	std_tty_printf("%c",0x3E);
}

void app_draw_endgame()
{
	std_tty_clrscr();
	std_tty_gotoxy(5,2);
	std_tty_printf("Game Over");
}
