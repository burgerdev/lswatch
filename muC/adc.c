
#include <avr/io.h>
#include "adc.h"

// input clock for adc must be 50kHz - 200kHz

// prescaler is 128
//#define PRESCALER (1<<ADPS0 | 1<<ADPS1 | 1<<ADPS2)
// prescaler is 32 - for 4MHz -> 125kHz
#define PRESCALER (1<<ADPS0 | 1<<ADPS2)

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
	ADCSRA = 1<<ADEN  | PRESCALER;
}