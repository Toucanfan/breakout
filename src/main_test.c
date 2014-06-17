#include <ez8.h> /* special encore constants, macros and falsh functions */
#include <sio.h> /* special encore serial i/o functions */
#include "std/text_input.h"
#include "std/draw.h"

void main(void)
{
	struct std_draw_point point;
	char str[4];
	char str_length = 4;

	point.x = 3;
	point.y = 3;

	std_text_input_create(&point, str, str_length);

	printf("%s", str);
}