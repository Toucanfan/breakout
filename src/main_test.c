#include <ez8.h> /* special encore constants, macros and falsh functions */
#include <sio.h> /* special encore serial i/o functions */
//#include "app/highscore.h"

void main(void)
{
	char key;
	char str[4];
	char i = 0;
	char input_loop = 1;

	init_uart(_UART0, _DEFFREQ, 115200);

	str[3] = '\0';

	while(input_loop){
		key = getch();
		if(97 <= key && key <= 122 && i < 3) {
			str[i] = key;
			i++;
		} else if(key == 127 && i > 0) {
			i--;
			str[i] = ' ';
		} else if(key == 13 && i > 0) {
			input_loop = 0;
		}

		printf("\n%s", str);
	}

	for(i++; i < 3; i++)
		str[i] = ' ';

	printf("\n\nYou entered: %s", str);

	while(1);
}