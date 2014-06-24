#include "std/kb.h"
#include "hal/kb.h"
#include "hal/button.h"

char std_kb_get_char()
{
	while(!hal_kb_hit() && hal_button_pressed() != HAL_BUTTON_B2){};

	if(hal_button_pressed() == HAL_BUTTON_B2)
		return ESC7;

	return UART_DATA_RECEIVE;
}
