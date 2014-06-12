#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H

#define HAL_BUTTON_NONE 0x0
#define HAL_BUTTON_B1 0x1 /* PD3 */
#define HAL_BUTTON_B2 0x2 /* PF6 */
#define HAL_BUTTON_B3 0x3 /* PF7 */


/* function prototypes */
extern char hal_button_pressed(void); /* currently pressed button */
extern char hal_button_new_press(void); /* button pressed since last call */


#endif /* hal/button.h */
