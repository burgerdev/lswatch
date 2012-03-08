
#include <avr/io.h>
#include "adc.h"

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

void adc_setup()
{
	// init ADC
	ADMUX = 1<<REFS0;
	ADCSRA = 1<<ADEN;
}