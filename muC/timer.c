/*                                          
    LSWatch, muC software for time measurement
    Copyright (C) 2012 Markus Döring

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/gpl.
*/




#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"



// heart-beat function, increments the clock by the amount computed in timer.h via an interrupt
ISR(TIMER1_CAPT_vect)
{
	if (is_started)
		timer_inc_lowest();
}


void start(void)
{
	reset();
	is_started = 1;
}

void stop(void)
{
	is_started = 0;
}

void reset(void)
{
	// ignore interrupts to avoid time corruptiom
	cli();

	time_h = 0;
	time_m = 0;
	time_s = 0;
	time_ms = 0;

	// allow interrupts
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



// timer incrementation functions, the milliseconds are incremented continuously, 
// a call to timer_add prepares all the time variables for reading
//
// overflow of time_ms occurs after 1100h, which should be enough

void timer_inc_h(void)
{
	time_h++;
	// error handling ommitted for PoC
}

void timer_inc_m(void)
{
	time_m++;
	while (time_m >= 60)
	{
		time_m -= 60;
		timer_inc_h();
	}
}

void timer_inc_s(void)
{
	time_s++;
	while (time_s >= 60)
	{
		time_s -= 60;
		timer_inc_m();
	}
}

void timer_inc_ms(uint16_t inc)
{
	time_ms += inc;
}

void timer_inc_lowest(void)
{
		timer_inc_ms(TIMER1_LOWEST_IN_MS);
}

void timer_add(void)
{
	while (time_ms >= 1000)
	{
		time_ms -= 1000;
		timer_inc_s();
	}
}
