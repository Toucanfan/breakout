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
		T1RL = 0x48;
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
	default:
		break;
	}
	EI(); // Enable interrupts globally
}

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

	default:
		break;
	}
	EI();
}

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

	default:
		break;
	}
	EI();
}

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
