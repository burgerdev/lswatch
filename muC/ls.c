#include <avr/io.h>
#include <util/delay.h>

#include "globals.h"
#include "adc.h"
#include "ls.h"



uint8_t broken(void)
{
	uint8_t sum = 0;
	for(int i=0;i<LS_N_ADC;i++) sum += getADC(LS_ADC_AVG) > LS_THRESH ? 1 : 0;
	if (sum<LS_N_HI)
		return 0;
	else
		return 1;

}

uint8_t broken_again(void)
{
	uint8_t sum = 0;
	for(int i=0;i<6;i++) sum += getADC(LS_ADC_AVG) > LS_THRESH ? 1 : 0;
	if (sum<LS_N_HI)
		return 0;
	else
		return 1;
	
}