#include <ez8.h> /* special encore constants, macros and falsh functions */
#include <sio.h> /* special encore serial i/o functions */
//#include "app/highscore.h"

void main(void)
{
	char ch;
/*	struct app_highscore score;
	score.score = 4;
	score.name = "bc";
	app_highscore_clr();
	app_add_highscore(score);
	app_render_highscore();*/

	init_uart(_UART0, _DEFFREQ, 115200);

	while(1){
		ch = getch();
		printf("%d\n", ch);
		printf("%c\n", ch);
	}
}