
#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"



// heart-beat function, increments the clock by 100th second
ISR(TIMER1_CAPT_vect)
{
	// disable interrupts in this function
	cli();
	if (is_started)
		timer_inc();
	// enable interrupts
	sei();
}


void start(void)
{
	cli();
	reset();
	is_started = 1;
	sei();
}

void stop(void)
{
	cli();
	is_started = 0;
	sei();
}

void reset(void)
{
	cli();
	time_h = 0;
	time_m = 0;
	time_s = 0;
	time_ms = 0;
	time_lowest = 0;
	sei();
}

void timer_setup(void)
{
	// set timer management
	TIMSK |= (1<<TICIE1);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | TIMER1_PRESCALER;
	ICR1H = TIMER1_COMPARE_VALUE >> 8;
	ICR1L = TIMER1_COMPARE_VALUE & 0xFF;

	// initialize flag
	is_started = 0;
}

void timer_inc_h(void)
{
	time_h++;
	// error handling ommitted for PoC
}

void timer_inc_m(void)
{
	time_m++;
	if (time_m == 60)
	{
		time_m = 0;
		timer_inc_h();
	}
}

void timer_inc_s(void)
{
	time_s++;
	if (time_s == 60)
	{
		time_s = 0;
		timer_inc_m();
	}
}

void timer_inc_ms(void)
{
	time_ms++;
	if (time_ms == 1000)
	{
		time_ms = 0;
		timer_inc_s();
	}
}

void timer_inc_lowest(void)
{
	time_lowest += TIMER1_COMPARE_INCREMENT;
	while (time_lowest > TIMER1_MAX)
	{
		time_lowest -= TIMER1_MAX;
		timer_inc_ms();
	}
}

void timer_inc()
{
	timer_inc_lowest();
}

