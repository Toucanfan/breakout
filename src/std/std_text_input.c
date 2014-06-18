#include "std/tty.h"
#include "std/draw.h"
#include "std/text_input.h"

/*
 * Initiates a text input. This function is blocking and will return when the user presses ENTER
 *
 * Arguments:
 *  - point is a pointer to the point where the input is graphically located
 *  - str: When the input is complete, this will be the entered text
 *  - str_length: MUST be the length (including null-terminator) of str
 *  - test_func: is a function pointer to a test function for the input
 *
 * Input characters can be limited using the test_func function. The function must return 0 (false) for illegal chars
 * and something else for legal. These characters will be ignored by the input handler.
 *
 * Example usages:
 *
 *     struct std_draw_point point;
 *     char str[4];
 *     char str_length = 4;
 *     point.x = 3; point.y = 1;
 *
 *     std_text_input_create(&point, str, str_length, &std_ti_letters_test);
 *
 * Here a 4 character text input is created at (3, 1) and only letters can be entered.
 */
void std_text_input_create(struct std_draw_point *point, char *str, char str_length, char (*test_func)(char input))
{
	char key;
	char i = 0;
	char input_loop = 1;

	str[str_length - 1] = '\0';

	while(input_loop){
		std_tty_gotoxy(point->x, point->y);
		std_tty_printf("%s", str);
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
	}

	for(i++; i < (str_length - 1); i++)
		str[i] = ' ';
}

/* Character input test functions. USe these to enable different kinds of text input */

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