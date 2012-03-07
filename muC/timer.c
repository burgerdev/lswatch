
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


void start()
{
        cli();
        reset();
        is_started = 1;
        sei();
}

void stop()
{
        cli();
        is_started = 0;
        sei();
}

void reset()
{
        cli();
        time_h = 0;
        time_m = 0;
        time_s = 0;
        time_cs = 0;
        sei();
}

void timer_inc_h()
{
        time_h++;
        // error handling ommitted for PoC
}

void timer_inc_m()
{
        time_m++;
        if (time_m == 60)
        {
                time_m = 0;
                timer_inc_h();
        }
}

void timer_inc_s()
{
        time_s++;
        if (time_s == 60)
        {
                time_s = 0;
                timer_inc_m();
        }
}

void timer_inc_cs()
{
        time_cs++;
        if (time_cs == 100)
        {
                time_cs = 0;
                timer_inc_s();
        }
}

void timer_inc()
{
        timer_inc_cs();
}

