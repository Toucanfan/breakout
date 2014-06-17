#include "std/tty.h"
#include "std/draw.h"
#include "std/text_input.h"

void std_text_input_create(struct std_draw_point *point, char *str, char str_length, char (*test_func)(char input))
{
	char key;
	char i = 0;
	char input_loop = 1;

	str[str_length - 1] = '\0';

	while(input_loop){
		std_tty_gotoxy(point->x + i, point->y);
		key = getch();
		if(test_func(key) && i < str_length - 1) {
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

char std_ti_number_test(char input)
{
    return 48 <= input && input <= 57;
}

char std_ti_letters_lowercase_test(char input)
{
    return 97 <= input && input <= 122;
}

char std_ti_letters_uppercase_test(char input)
{
    return 65 <= input && input <= 90;
}

char std_ti_letters_test(char input)
{
    return (65 <= input && input <= 90) || (97 <= input && input <= 122);
}

char std_ti_alphanum_test(char input)
{
    return (65 <= input && input <= 90) || (97 <= input && input <= 122) || (48 <= input && input <= 57);
}