#include "std/draw.h"
#include "std/tty.h"

void std_draw_box(struct std_draw_box *box)
{
	int i, j;
	std_tty_set_bcolor(box->color);
	for (i = box->tl.x; i <= br.x; i++) {
		for (j = box->tl.y; j <= box->br.y; j++) {
			std_tty_gotoxy(i, j);
			std_tty_printf(" ");
		}
	}
	std_tty_gotoxy(0, 0);
}

void std_draw_window(struct std_draw_window *window)
{
	int i, j;
	int textLength = 0;
	
	int width = window->br.x - window->tl.x + 1;
	int height = window->br.y - window->tl.y + 1;

	int headerExtra;

 	for(i = 0; window->title[i] != '\0'; i++) {
		textLength++;
	}

	headerExtra = width - 8 - textLength;

	std_tty_gotoxy(window->tl.x, window->tl.y);
	std_tty_printf("%c", window->style.tl);
	std_tty_printf("%c", window->style.hstart);
	std_tty_reverse(1);
	std_tty_printf("  %s  ", window->title);
	if(window->style.fill) {
		for(i = 0; i < headerExtra; i++) {
			std_tty_printf(" ");
		}
	}
	std_tty_reverse(0);
	std_tty_printf("%c", window->style.hend);
	if(!window->style.fill) {
		for(i = 0; i < headerExtra; i++) {
			std_tty_printf("%c", window->style.hori);
		}
	}
	std_tty_printf("%c\n", window->style.tr);
	
	for(i = 1; i < height; i++) {
		std_tty_gotoxy(window->tl.x, window->tl.y + i);
		std_tty_printf("%c", window->style.vert);
		for(j = 0; j < width - 2; j++) {
			std_tty_printf(" ");
		}
		std_tty_printf("%c", window->style.vert);
	}
	
	std_tty_gotoxy(window->tl.x, window->br.y);
	std_tty_printf("%c", window->style.bl);
	for(i = 0; i < width - 2; i++) {
		std_tty_printf("%c", window->style.hori);
	}
	std_tty_printf("%c", window->style.br);

	window->cursor.x = window->tl.x + 1;
	window->cursor.y = window->tl.y + 1;
}	
