#include <ez8.h>
#include "hal/timer.h"

static char flags = 0;

static void timer0_irq_handler(void)
{
	flags |= HAL_TIMER_0;
}

void hal_timer_init(void)
{
	DI(); // Disable interrupts globally
	T0CTL = 0x39; //Disable timer, enable cont. mode, set prescale to 0x80

	T0H = 0x00; //Set high order bits of preset
	T0L = 0x01; //Set low order bits of preset

	// We set the reload value to 0x48 (72) giving us a timer on 0.5 ms
	T0RH = 0x00; //Set high order bits of reload value
	T0RL = 0x48; //Set low order bits of reload value

	//Set IRQ priority to low
	IRQ0ENH = 0x00;
	IRQ0ENL = 0x20;

	T0CTL |= 0x80; //Enable timer
	SET_VECTOR(TIMER0, timer0_irq_handler); //Map irq handler
	EI(); // Enable interrupts globally
}

char hal_timer_read(char timer)
{
	char r = (flags & timer);
	flags &= ~r;
	return r;
}
