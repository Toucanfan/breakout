/**
 * @file
 * @author Troels Folke
 * @version 1.1
 * @section hal_timer-description Description
 * 
 * Abstracted implementation of timer configuration and usage
 *
 * HAL_TIMER_1 is twice as fast as 0, 2 and 3.
 *
 * @section hal_timer_usage Usage
 *
 * Setup af timer
 *
 *     hal_timer_configure(HAL_TIMER_1, 100);
 *
 * Start the timer
 *
 *     hal_timer_start(HAL_TIMER_1);
 *
 * Poll the timer
 *
 *     while(!hal_timer_read(HAL_TIMER_1);) {1}
 *     printf("Timer fired!");
 *
 * The subcount value can be used to control the "speed" of the timer.
 */

#include <ez8.h>
#include "hal/timer.h"

#define timer_count(NUM) \
{ \
	timerNUM_state.subcount++; \
	if (timerNUM_state.subcount == timerNUM_state.subcount_max) { \
		timerNUM_state.subcount = 0; \
		timerNUM_state.count++; \
	} \
}

static struct timer_state {
	int count;
	int subcount;
	int subcount_max;
};

static struct timer_state timer0_state;
static struct timer_state timer1_state;
static struct timer_state timer2_state;
static struct timer_state timer3_state;


#pragma interrupt
void timer0_irq_handler(void)
{
	timer0_state.subcount++;
	if (timer0_state.subcount == timer0_state.subcount_max) {
		timer0_state.subcount = 0;
		timer0_state.count++;
	}
}

#pragma interrupt
void timer1_irq_handler(void)
{
	timer1_state.subcount++;
	if (timer1_state.subcount == timer1_state.subcount_max) {
		timer1_state.subcount = 0;
		timer1_state.count++;
	}
}

#pragma interrupt
void timer2_irq_handler(void)
{
	timer2_state.subcount++;
	if (timer2_state.subcount == timer2_state.subcount_max) {
		timer2_state.subcount = 0;
		timer2_state.count++;
	}
}

#pragma interrupt
void timer3_irq_handler(void)
{
	timer3_state.subcount++;
	if (timer3_state.subcount == timer3_state.subcount_max) {
		timer3_state.subcount = 0;
		timer3_state.count++;
	}
}

//! Configures a timer
/**
 * @param timer The timer to configure
 * @param subcount_max The number the timer/counter should count to before "firing"
 */
void hal_timer_configure(char timer, int subcount_max)
{
	DI(); // Disable interrupts globally

	switch (timer) {
	case HAL_TIMER_0:
		//Enable cont. mode, set prescale to 0x80
		T0CTL |= 0x39; 
		T0H = 0x00; //Set high order bits of preset
		T0L = 0x01; //Set low order bits of preset

		// We set the reload value to 0x48 (72) giving us a 
		// timer on 0.5 ms
		T0RH = 0x00; //Set high order bits of reload value
		T0RL = 0x48; //Set low order bits of reload value

		//Set IRQ priority to low
		IRQ0ENH &= ~0x20;
		IRQ0ENL |= 0x20;

		timer0_state.subcount_max = subcount_max;

		SET_VECTOR(TIMER0, timer0_irq_handler); //Map irq handler
		break;
	case HAL_TIMER_1:
		T1CTL |= 0x39; 
		T1H = 0x00;
		T1L = 0x01;
		T1RH = 0x00;
		T1RL = 0x24;
		IRQ0ENH &= ~0x40;
		IRQ0ENL |= 0x40;
		timer1_state.subcount_max = subcount_max;
		SET_VECTOR(TIMER1, timer1_irq_handler);
		break;
	case HAL_TIMER_2:
		T1CTL |= 0x39; 
		T1H = 0x00;
		T1L = 0x01;
		T1RH = 0x00;
		T1RL = 0x48;
		IRQ0ENH &= ~0x80;
		IRQ0ENL |= 0x80;
		timer2_state.subcount_max = subcount_max;
		SET_VECTOR(TIMER2, timer2_irq_handler);
		break;
	case HAL_TIMER_3:
		T3CTL |= 0x39; 
		T3H = 0x00;
		T3L = 0x01;
		T3RH = 0x00;
		T3RL = 0x48;
		IRQ2ENH &= ~0x80;
		IRQ2ENL |= 0x80;
		timer2_state.subcount_max = subcount_max;
		SET_VECTOR(TIMER3, timer3_irq_handler);
		break;
	default:
		break;
	}
	EI(); // Enable interrupts globally
}

//! Starts a timer
/**
 * @param timer The timer to start
 */
void hal_timer_start(char timer)
{
	DI();
	switch (timer) {
	case HAL_TIMER_0:
		T0CTL |= 0x80; //Enable timer
		break;

	case HAL_TIMER_1:	
		T1CTL |= 0x80;
		break;
	
	case HAL_TIMER_2:
		T2CTL |= 0x80;
		break;

	case HAL_TIMER_3:
		T3CTL |= 0x80;
		break;

	default:
		break;
	}
	EI();
}

//! Stops a timer
/**
 * @param timer The timer to stop
 */
void hal_timer_stop(char timer)
{
	DI();
	switch (timer) {
	case HAL_TIMER_0:
		T0CTL &= ~0x80; //Disable timer
		break;

	case HAL_TIMER_1:	
		T1CTL &= ~0x80;
		break;
	
	case HAL_TIMER_2:
		T2CTL &= ~0x80;
		break;

	case HAL_TIMER_3:
		T3CTL &= ~0x80;
		break;

	default:
		break;
	}
	EI();
}
//! Read if a timer has fired
/**
 * @param timer The timer to read
 */
int hal_timer_read(char timer)
{
	int r = 0;

	switch (timer) {
	case HAL_TIMER_0:
		r = timer0_state.count;
		timer0_state.count = 0;
		break;

	case HAL_TIMER_1:	
		r = timer1_state.count;
		timer1_state.count = 0;
		break;
	
	case HAL_TIMER_2:
		r = timer2_state.count;
		timer2_state.count = 0;
		break;

	default:
		break;
	}

	return r;
}
