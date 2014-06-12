#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H

#define HAL_BUTTON_B1 0x1
#define HAL_BUTTON_B2 0x2
#define HAL_BUTTON_B3 0x3


/* function prototypes */
void hal_button_init(char button);
char hal_button_pressed(char button);


#endif /* hal/button.h */
