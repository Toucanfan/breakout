#ifndef HAL_LED_H
#define HAL_LED_H

/* led mode flags */
#define HAL_LED_ON 0x1
#define HAL_LED_BLINK 0x2
#define HAL_LED_SCROLL 0x4

/* function prototypes */
extern void hal_led_init(void);
extern void hal_led_refresh(void);
extern void hal_led_set_string(char *str);

#endif /* hal/led.h */
