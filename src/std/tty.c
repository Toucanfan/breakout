#include "std/tty.h"

#define ESC "\x1B"

void std_tty_clrscr(void) {
	std_tty_printf(ESC"[2J"ESC"[1;1H");
}

void std_tty_clreol(void) {
	std_tty_printf(ESC"[K");
}

void std_tty_gotoxy(int x, int y) {
	std_tty_printf(ESC"[%d;%dH", y, x);
}

void std_tty_underline(int on) {
	if (on)
		std_tty_printf(ESC"[4m");
	else
		std_tty_printf(ESC"[24m");
}

void std_tty_reverse(int on) {
	if (on) {
		std_tty_printf(ESC"[7m");
	} else {
		std_tty_printf(ESC"[27m");
	}
}

void std_tty_blink(int on) {
	if (on) {
		std_tty_printf(ESC"[5m");
	} else {
		std_tty_printf(ESC"[25m");
	}
}
