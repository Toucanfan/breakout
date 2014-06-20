#include <uart.h>
#include <ez8.h>
#include "std/kb.h"
#include "hal/button.h"

char get_char()
{
	while(!kbhit() && hal_button_pressed() != HAL_BUTTON_B2){};

	if(hal_button_pressed() == HAL_BUTTON_B2)
		return ESC7;

	return U0RXD;
}