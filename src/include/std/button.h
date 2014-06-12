#ifndef STD_BUTTON_H
#define STD_BUTTON_H

#include "hal/button.h"

#define STD_BUTTON_NONE HAL_BUTTON_NONE
#define STD_BUTTON_LEFT HAL_BUTTON_B1
#define STD_BUTTON_MIDDLE HAL_BUTTON_B2
#define STD_BUTTON_RIGHT HAL_BUTTON_B3

/* macro functions */
#define std_button_new_press() hal_button_new_press()
#define std_button_pressed() hal_button_pressed()


#endif /* std/button.h */
