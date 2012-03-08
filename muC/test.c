 
#include "globals.h"

#include <avr/io.h>          
#include <avr/interrupt.h>
#include <util/delay.h> 

#include "disp.h"
#include "timer.h"
#include "adc.h"


void SWAP_STATE(void)
{	
	if ( (PORTC & 1<<PC1) == (1<<PC1))
	 	PORTC &= ~(1<<PC1);
	else	
		PORTC |= 1<<PC1;
}

uint8_t SAME(void)
{
	uint8_t ans = 0;
	ans = (PINC & 1<<PC0) | (PORTC & 1<<PC1);

	if ( (ans & ((1<<PC0) | (1<<PC1))) == ((1<<PC0)|(1<<PC1))  || ans == 0)
		ans = 1;
	else
		ans = 0;
	return ans;

}

void loop_main(void);

void loop_main_test(void);




int main(void)
{
	cli();

	// B is output
	DDRB = 0xFF;
	PORTB = 0x00;

	// C is input
	DDRC = 0x00;
	PORTC = 0xFF;
	
	DDRC |= 1<<PC1;
	PORTC &= ~(1<<PC1 | 1<<PC0);

	// D is input
	DDRD = 0;
	PORTD |= ~(1<<PD7);
	
	adc_setup();
	
	

	timer_setup();

	// enable interrupts, start loop
	sei();
	while (1)
	{
		//loop_main();
		//loop_main_test();
		loop_main();
		//blink(1);
	}

	return 0;
}


#define FM_HI() PORTC |= 1<<PC1
#define FM_LO() PORTC &= ~(1<<PC1)


void loop_main()
{
	uint16_t n = 0;
	uint16_t result=0;

	while (1)
	{
		n++;
		result = 0;
		
		FM_HI();
		
		_delay_ms(500);
		
		FM_LO();
		
		start();
		while ((result = getADC(1)/128) >= 6);
		stop();

		result = time_lowest/1000;

		result = result>7?7:result;
		
		disp(time_ms);
		//disp(id>5?7:1);
		//disp( (uint8_t) id);
		
		_delay_ms(1000);
		disp_off();
		_delay_ms(100);
		
		
	}
}


void loop_main_test()
{

	for (int c=1;c<8;c++)
	{
		start();
		while (!time_s);
		stop();
		disp(c);
	}
	
}
