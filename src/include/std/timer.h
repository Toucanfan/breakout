#include "hal/timer.h"

#define STD_TIMER_0 HAL_TIMER_0
#define STD_TIMER_1 HAL_TIMER_1
#define STD_TIMER_2 HAL_TIMER_2

#define std_timer_read(t) (hal_timer_read(t))
#define std_timer_configure(t, s) hal_timer_configure(t, s)
#define std_timer_start(t) hal_timer_start(t)
#define std_timer_stop(t) hal_timer_stop(t)
