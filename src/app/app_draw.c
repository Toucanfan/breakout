#include "std/draw.h"
#include "std/tty.h"
#include "app/draw.h"

#define splash_offset_x 20
#define splash_offset_y 30

void app_draw_splash(void) 
{
const char* Title[] = { "first", "second", "third" };


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
	std_tty_gotoxy(5,2);
	std_tty_printf("GAME SON");
	std_tty_gotoxy(5,3);
	std_tty_printf("HIGHSCORES SON");
	std_tty_gotoxy(5,4);
	std_tty_printf("HELP SON");
	std_tty_gotoxy(5,5);
	std_tty_printf("EXIT SON");
	
	std_tty_gotoxy(3,selection+2);
	std_tty_printf("%c",0x3E);
}

void app_draw_help(void)
{
	std_tty_clrscr();
	std_tty_gotoxy(1,1);
	std_tty_printf("help yo motherfucker");
}

void app_draw_difficulties(char selection)
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


