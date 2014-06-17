#ifndef STD_TTY_H
#define STD_TTY_H

#include "hal/uart.h"

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
