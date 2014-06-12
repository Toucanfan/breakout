#ifndef STD_TTY_H
#define STD_TTY_H

#include <sio.h>

/* macro functions */
#define std_tty_printf printf

/* function prototypes */
void std_tty_clrscr(void);
void std_tty_clreol(void);
void std_tty_gotoxy(int x, int y);
void std_tty_underline(char boolean);
void std_tty_reverse(char boolean);
void std_tty_blink(char boolean);


#endif /* std/tty.h */
