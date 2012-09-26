 
#include "globals.h"

#include <avr/io.h>          
#include <avr/interrupt.h>
#include <util/delay.h> 

#include "disp.h"
#include "timer.h"
#include "adc.h"
#include "lcd-routines.h"
#include "ls.h"


void loop_main(void);

// basic ls loop
void loop_main_test(void);

// displays transmission information
void loop_main_radio_check(void);




int main(void)
{
	cli();

	
	// B is output for LCD
	DDRB = 0xFF;
	PORTB = 0x00;

	// C is input, except PC5 (C0 is ADC for radio)
	DDRC = 1<<PC5;
	PORTC = 1<<PC5;
	

	// D is input for button to GND
	DDRD = 0;
	PORTD = 0xFF;
	
	
	adc_setup(); 

	lcd_init();
	disp(0);
	

	timer_setup();

	// enable interrupts, start loop
	sei();
	while (1)
	{
		// if button pressed, show radio check, otherwise start timing loop
		if (PIND & 1<<PD0)
			loop_main_test();
		else
			loop_main_radio_check();

	}

	return 0;
}



void loop_main()
{
	uint8_t first = 1;
	while(1)
	{
		if (first)
		{
			if (broken())
			{
				start();

				if (broken_again())
				{
					first = 0;
					disp_str("...");

					_delay_ms(LS_WAIT_TIME_MS);
				}
				else
				{
					stop();
				}
				
			}
		}
		else
		{
			if (broken())
			{
				if (broken_again())
				{
					stop();
					disp(time_ms/10);
					first = 1;

					_delay_ms(LS_WAIT_TIME_MS);
				}
			}
		}

			
		//else
		//	_delay_ms(10);
	}
}


void loop_main_radio_check()
{
	while(1)
	{

		// one ADC(1024) takes 120ms
		// -> 640*ADC(16) takes 1.2s
		uint32_t sum = 0;
		for (uint16_t k=0; k<640; k++)
			sum += getADC(16) > LS_THRESH ? 1 : 0;

		// percents
		sum = (sum * 10000)/640;
		
		disp_percent((uint16_t)sum);
	}
	
}

void loop_main_test()
{
	uint8_t first = 1;
	while(1)
	{
		if (broken())
		{
			if (first)
			{
				start();
				first = 0;
				disp_str("...");
			}
			else
			{
				stop();
				// empirical correction factor will be applied
				disp(time_ms/10);
				//disp( (time_ms*600)/5840);
				first = 1;
			}
			_delay_ms(LS_WAIT_TIME_MS);
		}
		//else
		//	_delay_ms(10);
	}
	
}
