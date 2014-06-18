#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#define HAL_TIMER_0 0x1
#define HAL_TIMER_1 0x2
#define HAL_TIMER_2 0x4

extern char hal_timer_read(char timer);
extern char hal_timer_init(void);

#endif /* hal/timer.h */
