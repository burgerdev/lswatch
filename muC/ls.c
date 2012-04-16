#include <avr/io.h>
#include <util/delay.h>

#include "globals.h"
#include "adc.h"


// one call to getADC takes 2.1ms with prescaler 128 at 4MHz
// number of times the ADC is called
#define LS_N_ADC 2
// number of times ADC must be greater than threshold to count as broken
#define LS_N_HI 2
// threshold
#define LS_THRESH 900
// averages ADC
#define LS_ADC_AVG 16

uint8_t broken(void)
{
	uint8_t sum = 0;
	for(int i=0;i<LS_N_ADC;i++) sum += getADC(LS_ADC_AVG) > LS_THRESH ? 1 : 0;
	if (sum<LS_N_HI)
		return 0;
	else
		return 1;

}