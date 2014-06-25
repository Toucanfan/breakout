/**
 * @file
 * @author Henrik Enggaard Hansen <henrik.enggaard@gmail.com>
 * @version 1.0
 * @section std_ti-description Description
 * 
 * A general purpose text input field for keyboard input from a UART connected terminal.
 * 
 * @section std_ti-usage Usage
 *
 *     struct std_draw_point point;
 *     char str[4];
 *     char str_length = 4;
 *     point.x = 3; point.y = 1;
 *
 *     std_ti_create(&point, str, str_length, &std_ti_letters_test);
 *
 * Here a 4 character text input is created at (3, 1) and only letters can be entered.
 */

#include "std/button.h"
#include "std/tty.h"
#include "std/draw.h"
#include "std/ti.h"
#include "std/kb.h"

//! Initiates a text input.
/**
 * This function is blocking and will return when the user presses ENTER
 *
 * Input characters can be limited using the test_func function. The function must return 0 (false) for illegal chars
 * and something else for legal. These characters will be ignored by the input handler.
 *
 * @param point The origin point of the text input
 * @param str The string which the text will be "entered" into
 * @param str_length MUST be the length (including null-terminator) of `str`
 * @param test_func The test function for allowed characters
 */
void std_ti_create(struct std_draw_point *point, char *str, char str_length, char (*test_func)(char input))
{
	char key;
	char i = 0;
	char input_loop = 1;

	str[str_length - 1] = '\0';

	while(input_loop){
		std_tty_gotoxy(point->x, point->y);
		std_tty_printf("%s", str);
		std_tty_gotoxy(point->x + i, point->y);

		key = std_kb_get_char();
		if(test_func(key) && i < str_length - 1) {
			str[i] = key;
			i++;
		} else if(key == STD_KB_BACKSPACE && i > 0) {
			i--;
			str[i] = ' ';
		} else if(key == STD_KB_ENTER && i > 0) {
			input_loop = 0;
		} else if(key == STD_KB_ESC27 || key == STD_KB_ESC7) {
			for(i = 0; i < str_length - 1; i++) {
				str[i] = ' ';
			}
			input_loop = 0;
		}
	}

	for(++i; i < (str_length - 1); i++)
		str[i] = ' ';
}


//! Test function for number chars
char std_ti_number_test(char input)
{
    return 48 <= input && input <= 57;
}

//! Test function for lowercase chars
char std_ti_letters_lowercase_test(char input)
{
    return 97 <= input && input <= 122;
}

//! Test function for uppercase chars
char std_ti_letters_uppercase_test(char input)
{
    return 65 <= input && input <= 90;
}

//! Test function for upper- and lowercase chars
char std_ti_letters_test(char input)
{
    return (65 <= input && input <= 90) || (97 <= input && input <= 122);
}

//! Test function for all letters and numbers chars
char std_ti_alphanum_test(char input)
{
    return (65 <= input && input <= 90) || (97 <= input && input <= 122) || (48 <= input && input <= 57);
}
