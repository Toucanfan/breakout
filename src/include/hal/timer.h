#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#define HAL_TIMER_0 0x1
#define HAL_TIMER_1 0x2
#define HAL_TIMER_2 0x4
#define HAL_TIMER_3 0x8

extern int hal_timer_read(char timer);
extern void hal_timer_configure(char timer, int subcount_max);
extern void hal_timer_start(char timer);
extern void hal_timer_stop(char timer);

#endif /* hal/timer.h */
