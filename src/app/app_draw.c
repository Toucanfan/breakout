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

void app_draw_splash(void) 
{
	char *strings[SPLASH_ROWS] = { 
		"                                                                                                                                            dddddddd", 
		"               AAA                                 kkkkkkkk                                                               iiii              d::::::d", 
		"              A:::A                                k::::::k                                                              i::::i             d::::::d",
		"             A:::::A                               k::::::k                                                               iiii              d::::::d",
		"            A:::::::A                              k::::::k                                                                                 d:::::d ",
		"           A:::::::::A          rrrrr   rrrrrrrrr   k:::::k    kkkkkkkaaaaaaaaaaaaa  nnnn  nnnnnnnn       ooooooooooo   iiiiiii     ddddddddd:::::d ",
		"          A:::::A:::::A         r::::rrr:::::::::r  k:::::k   k:::::k a::::::::::::a n:::nn::::::::nn   oo:::::::::::oo i:::::i   dd::::::::::::::d ",
		"         A:::::A A:::::A        r:::::::::::::::::r k:::::k  k:::::k  aaaaaaaaa:::::an::::::::::::::nn o:::::::::::::::o i::::i  d::::::::::::::::d ",
		"        A:::::A   A:::::A       rr::::::rrrrr::::::rk:::::k k:::::k            a::::ann:::::::::::::::no:::::ooooo:::::o i::::i d:::::::ddddd:::::d ",
		"       A:::::A     A:::::A       r:::::r     r:::::rk::::::k:::::k      aaaaaaa:::::a  n:::::nnnn:::::no::::o     o::::o i::::i d::::::d    d:::::d ",
		"      A:::::AAAAAAAAA:::::A      r:::::r     rrrrrrrk:::::::::::k     aa::::::::::::a  n::::n    n::::no::::o     o::::o i::::i d:::::d     d:::::d ",
		"     A:::::::::::::::::::::A     r:::::r            k:::::::::::k    a::::aaaa::::::a  n::::n    n::::no::::o     o::::o i::::i d:::::d     d:::::d ",
		"    A:::::AAAAAAAAAAAAA:::::A    r:::::r            k::::::k:::::k  a::::a    a:::::a  n::::n    n::::no::::o     o::::o i::::i d:::::d     d:::::d ",
		"   A:::::A             A:::::A   r:::::r           k::::::k k:::::k a::::a    a:::::a  n::::n    n::::no:::::ooooo:::::oi::::::id::::::ddddd::::::dd",
		"  A:::::A               A:::::A  r:::::r           k::::::k  k:::::ka:::::aaaa::::::a  n::::n    n::::no:::::::::::::::oi::::::i d:::::::::::::::::d",
		" A:::::A                 A:::::A r:::::r           k::::::k   k:::::ka::::::::::aa:::a n::::n    n::::n oo:::::::::::oo i::::::i  d:::::::::ddd::::d",
		"AAAAAAA                   AAAAAAArrrrrrr           kkkkkkkk    kkkkkkkaaaaaaaaaa  aaaa nnnnnn    nnnnnn   ooooooooooo   iiiiiiii   ddddddddd   ddddd"
	};

	int i;

	std_tty_clrscr();
	std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);
	for (i = 0; i < SPLASH_ROWS; i++) {
		std_tty_gotoxy(SPLASH_OFFSET_X,SPLASH_OFFSET_Y+i);
		std_tty_printf("%s",strings[i]);
	}


}

void app_draw_highscores(void)
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	app_render_highscore();
}


void app_draw_difficulties(char selection)
{	
	int init = 1;
	int i;
	int j;
	static int prior_selection = 3;

	char *easy[] = { 
		" ______           _______     __", 
		"|  ____|   /\\    / ____\\ \\   / /", 
		"| |__     /  \\  | (___  \\ \\_/ / ",
		"|  __|   / /\\ \\  \\___ \\  \\   /  ",
		"| |____ / ____ \\ ____) |  | |  ",
		"|______/_/    \\_\\_____/   |_|   "
	};



	char *normal[] = { 
		" _   _  ____  _____  __  __          _    ", 
		"| \\ | |/ __ \\|  __ \\|  \\/  |   /\\   | |     ", 
		"|  \\| | |  | | |__) | \\  / |  /  \\  | |     ",
		"| . ` | |  | |  _  /| |\\/| | / /\\ \\ | |     ",
		"| |\\  | |__| | | \\ \\| |  | |/ ____ \\| |____ ",
		"|_| \\_|\\____/|_|  \\_\\_|  |_/_/    \\_\\______|"
	};



	char *hard[] = { 
		" _    _          _____  _____  ", 
		"| |  | |   /\\   |  __ \\|  __ \\ ", 
		"| |__| |  /  \\  | |__) | |  | |",
		"|  __  | / /\\ \\ |  _  /| |  | |",
		"| |  | |/ ____ \\| | \\ \\| |__| |",
		"|_|  |_/_/    \\_\\_|  \\_\\_____/ "
	};


	char *very_hard[] = { 
		"__      ________ _______     __  _    _          _____  _____  ", 
		"\\ \\    / /  ____|  __ \\ \\   / / | |  | |   /\\   |  __ \\|  __ \\ ", 
		" \\ \\  / /| |__  | |__) \\ \\_/ /  | |__| |  /  \\  | |__) | |  | |",
		"  \\ \\/ / |  __| |  _  / \\   /   |  __  | / /\\ \\ |  _  /| |  | |",
		"   \\  /  | |____| | \\ \\  | |    | |  | |/ ____ \\| | \\ \\| |__| |",
		"    \\/   |______|_|  \\_\\ |_|    |_|  |_/_/    \\_\\_|  \\_\\_____/ "
	};
    
	char **difficulties[DIFFICULTY_AMOUNT];
	difficulties[0] = easy;
	difficulties[1] = normal;
	difficulties[2] = hard;
	difficulties[3] = very_hard;

	std_tty_clrscr();
	std_tty_set_fcolor(STD_TTY_FCOLOR_GREEN);

	if (init) {
		// draw all
		for (j = 0; j < DIFFICULTY_AMOUNT; j++)
			for (i = 0; i < DIFFICULTY_ROWS; i++) {
			std_tty_gotoxy(DIFFICULTY_OFFSET_X,DIFFICULTY_OFFSET_Y+(DIFFICULTY_INTERDIST_Y+DIFFICULTY_ROWS)*prior_selection+i);
			std_tty_printf("%s",difficulties[j][i]);
			}
	} else {
		// redraw old
		for (i = 0; i < DIFFICULTY_ROWS; i++) {
		std_tty_gotoxy(DIFFICULTY_OFFSET_X,DIFFICULTY_OFFSET_Y+(DIFFICULTY_INTERDIST_Y+DIFFICULTY_ROWS)*prior_selection+i);   
		std_tty_printf("%s",difficulties[prior_selection][i]);
		}
	} 
	
	// highlight selection
	std_tty_blink(1);
	std_tty_set_fcolor(STD_TTY_FCOLOR_RED);
	for (i = 0; i < DIFFICULTY_ROWS; i++) {
		std_tty_gotoxy(DIFFICULTY_OFFSET_X,DIFFICULTY_OFFSET_Y+(DIFFICULTY_INTERDIST_Y+DIFFICULTY_ROWS)*selection+i);
		std_tty_printf("%s",difficulties[selection][i]);
	}
	std_tty_blink(0);

	prior_selection = selection;
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

