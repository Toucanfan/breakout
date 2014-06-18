#ifndef STD_TTY_H
#define STD_TTY_H

#include "hal/uart.h"

#define STD_TTY_BCOLOR_BLACK	0
#define STD_TTY_BCOLOR_RED	1
#define STD_TTY_BCOLOR_GREEN	2
#define STD_TTY_BCOLOR_BROWN	3
#define STD_TTY_BCOLOR_BLUE	4
#define STD_TTY_BCOLOR_PURPLE	5
#define STD_TTY_BCOLOR_CYAN	6
#define STD_TTY_BCOLOR_GRAY	7

#define STD_TTY_FCOLOR_BLACK	0
#define STD_TTY_FCOLOR_RED	1
#define STD_TTY_FCOLOR_GREEN	2
#define STD_TTY_FCOLOR_BROWN	3
#define STD_TTY_FCOLOR_BLUE	4
#define STD_TTY_FCOLOR_PURPLE	5
#define STD_TTY_FCOLOR_CYAN	6
#define STD_TTY_FCOLOR_GRAY	7
#define STD_TTY_FCOLOR_DGRAY	8
#define STD_TTY_FCOLOR_LRED	9
#define STD_TTY_FCOLOR_LGREEN	10
#define STD_TTY_FCOLOR_YELLOW	11
#define STD_TTY_FCOLOR_LBLUE	12
#define STD_TTY_FCOLOR_LPURPLE	13
#define STD_TTY_FCOLOR_LCYAN	14
#define STD_TTY_FCOLOR_WHITE	15

/* macro functions */
#define std_tty_printf printf
#define std_tty_init() hal_uart_init()

/* function prototypes */
void std_tty_clrscr(void);
void std_tty_clreol(void);
void std_tty_gotoxy(int x, int y);
void std_tty_underline(char boolean);
void std_tty_reverse(char boolean);
void std_tty_blink(char boolean);
void std_tty_set_bcolor(char bcolor);
void std_tty_set_fcolor(char fcolor);

/* Keycodes */
#define ENTER 13
#define BACKSPACE 127
#define SPACE 32
#define ARROWUP 5	
#define ARROWDOWN 6
#define ARROWRIGHT 7
#define ARROWLEFT 8
#define ESC7 7
#define ESC27 27
#define TAB 9

#endif /* std/tty.h */
