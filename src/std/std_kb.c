/**
 * @file
 * @author Henrik Enggaard Hansen <henrik.enggaard@gmail.com>
 * @version 2.0
 * @section std_kb-description Description
 *
 * Receive keyboard input from serial terminal.
 */

#include "std/kb.h"
#include "hal/kb.h"
#include "hal/button.h"

char std_kb_get_char()
//! Wait and return char from keyboard input
/**
 * This is function will block execution until
 *
 *  1. a key is pressed on the keyboard
 *  2. button 2 is pressed on the dev board
 *
 * @return ASCII-code of the key pressed. Esc if button is pressed.
 */
{
	while(!hal_kb_hit() && hal_button_pressed() != HAL_BUTTON_B2){};

	if(hal_button_pressed() == HAL_BUTTON_B2)
		return STD_KB_ESC7;

	return UART_DATA_RECEIVE;
}
