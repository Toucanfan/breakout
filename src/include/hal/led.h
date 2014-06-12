#ifndef HAL_LED_H
#define HAL_LED_H

#include <ez8.h>

/* macro functions */
#define hal_irq_disable() DI()
#define hal_irq_enable() EI()

/* function prototypes */
extern void hal_led_init(void);
extern void hal_led_refresh(void);

extern void hal_timer_init(void);

#endif /* hal/led.h */
