#include "std/tty.h"
#include "std/draw.h"
#include "std/text_input.h"

void std_text_input_create(struct std_draw_point *point, char *str, char str_length)
{
	char key;
	char i = 0;
	char input_loop = 1;

	str[str_length - 1] = '\0';

	while(input_loop){
		std_tty_gotoxy(point->x + i, point->y);
		key = getch();
		if(97 <= key && key <= 122 && i < 3) {
			str[i] = key;
			i++;
		} else if(key == BACKSPACE && i > 0) {
			i--;
			str[i] = ' ';
		} else if(key == ENTER && i > 0) {
			input_loop = 0;
		}


		std_tty_gotoxy(point->x, point->y);
		std_tty_printf("%s", str);
	}

	for(i++; i < (str_length - 1); i++)
		str[i] = ' ';
}