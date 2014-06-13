#include <ez8.h>
#include "hal/button.h"

char hal_button_pressed(void)
{
	if (~PDIN & 0x08) //PD3
		return HAL_BUTTON_B1;
	else if (~PFIN & 0x40) //PF6
		return HAL_BUTTON_B2;
	else if (~PDIN & 0x80) //PF7
		return HAL_BUTTON_B3;
	else
		return HAL_BUTTON_NONE;
}

char hal_button_new_press(void)
{
	static char button_old = HAL_BUTTON_NONE;
	char button = hal_button_pressed();
	char rval = (button == button_old) ? HAL_BUTTON_NONE : button;
	button_old = button;
	return rval;
}
