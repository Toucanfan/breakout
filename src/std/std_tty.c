/**
 * @file
 * @version 1.0
 * @section std_tty-description Description
 *
 * Functions for controlling ANSI printing for serial terminal
 */

#include "std/tty.h"

#define ESC "\x1B"

//! Clear to end of line
void std_tty_clreol(void) {
	std_tty_printf(ESC"[K");
}

//! Move cursor to (x, y)
void std_tty_gotoxy(int x, int y) {
	std_tty_printf(ESC"[%d;%dH", y, x);
}

//! Set underline style
/**
 * @param on 1 for underline on, 0 for off
 */
void std_tty_underline(char on) {
	if (on)
		std_tty_printf(ESC"[4m");
	else
		std_tty_printf(ESC"[24m");
}

//! Set reversed color style
/**
 * @param on 1 for on, 0 for off
 */
void std_tty_reverse(char on) {
	if (on) {
		std_tty_printf(ESC"[7m");
	} else {
		std_tty_printf(ESC"[27m");
	}
}

//! Set blink style
/**
 * @param on 1 for on, 0 for off
 */
void std_tty_blink(char on) {
	if (on) {
		std_tty_printf(ESC"[5m");
	} else {
		std_tty_printf(ESC"[25m");
	}
}

//! Set foreground color
/**
 * @param fcolor The color
 */
void std_tty_set_fcolor(char fcolor)
{
	int type = 22;
	if (fcolor > 7) {
		type = 1;
		fcolor -= 8;
	}
	std_tty_printf(ESC"[%d;%dm", type, fcolor+30);
}

//! Set background color
/**
 * @param bcolor The color
 */
void std_tty_set_bcolor(char bcolor)
{
	std_tty_printf(ESC"[%dm", bcolor+40);
}

//! Clear screen
void std_tty_clrscr(void) {
	std_tty_set_bcolor(STD_TTY_BCOLOR_BLACK);
	std_tty_printf(ESC"[2J"ESC"[1;1H");
	std_tty_printf(ESC"[?25l");
}
