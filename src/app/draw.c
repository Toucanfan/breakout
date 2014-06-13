#include "std/draw.h"
#include "std/tty.h"
#indclude "app/draw.h"

void app_draw_splash(void) 
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	std_tty_printf("Splash motherfucker");
}

void app_draw_highscores(void)
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	std_tty_printf("highscores bitch");
}

void app_draw_menu(char selection)
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	std_tty_printf("GAME SON");
	std_tty_gotoxy(1,1);
	std_tty_printf("GAME SON");
	std_tty_gotoxy(1,1);
	std_tty_printf("GAME SON");
	std_tty_gotoxy(1,1);
	std_tty_printf("GAME SON");
	std_tty_gotoxy(1,1);
	std_tty_printf("GAME SON");
