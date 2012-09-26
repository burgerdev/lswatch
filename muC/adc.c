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




#include <avr/io.h>
#include "adc.h"

// input clock for adc must be 50kHz - 200kHz

// prescaler is 32 - for 4MHz -> 125kHz
#define PRESCALER (1<<ADPS0 | 1<<ADPS2)

// get the value of the ADC, average over 'n' times
uint16_t getADC(uint16_t n)
{
	
	uint32_t sum = 0;
	
	uint16_t sample = 0;
	
	for(int i=0;i<n;i++)
	{
		sample = 0;
		ADCSRA |= 1<<ADSC;
		while ( (ADCSRA & 1<<ADSC));
		sample = ADCL | ADCH<<8;
		sum += sample;
	}
	
	sum  = sum / n;
	
	sample = (uint16_t) sum;
	
	return sample;
}

// setup for analog digital conversion
void adc_setup()
{
	// init ADC
	ADMUX = 1<<REFS0;
	ADCSRA = 1<<ADEN  | PRESCALER;
}
