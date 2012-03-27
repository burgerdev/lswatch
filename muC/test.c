 
#include "globals.h"

#include <avr/io.h>          
#include <avr/interrupt.h>
#include <util/delay.h> 

#include "disp.h"
#include "timer.h"
#include "adc.h"
#include "lcd-routines.h"


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
	PORTD = 0xFF;
	/*
	adc_setup(); */


	/*
	// init the lcd_c
	DDRC = 0xFF;
	PORTC = 0x00;
	_delay_ms(500);

	// 4bit mode
	PORTC = 0b0010;
	lcd_enable();

	// 4bit, 2 lines, 5x7
	PORTC = 0b0010;
	lcd_enable();
	PORTC = 0b1000;
	lcd_enable();

	// disp on, cursor on, blink on
	PORTC = 0b0000;
	lcd_enable();
	PORTC = 0b1111;
	lcd_enable();

	// clear
	PORTC = 0b0000;
	lcd_enable();
	PORTC = 0b0001;
	lcd_enable();
	
	// auto-increment
	PORTC = 0b0000;
	lcd_enable();
	PORTC = 0b0110;
	lcd_enable();

	lcd_data('T');
	lcd_data('T');
	lcd_data('T');
	lcd_data('T');

	_delay_ms(1000);
	lcd_clear();
	*/

	lcd_init();
	disp(0);
	

	timer_setup();

	// enable interrupts, start loop
	sei();
	while (1)
	{
		//loop_main();
		loop_main_test();
		//loop_main();
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

uint8_t button_pressed(void)
{
	uint8_t ret = 1;
	if (PIND & 1<<PD2)
	{
		ret = 0;
	}
	else
	{
		_delay_ms(10);
		if (PIND & 1<<PD2)
			ret = 0;
		else
		{
			ret = 1;
			
		}
		
	}
}


void loop_main_test()
{
	uint8_t first = 1;
	while(1)
	{
		if (button_pressed())
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
				disp(time_s*100 + time_ms/10);
				first = 1;
			}
			_delay_ms(500);
		}
		else
			_delay_ms(10);
	}
	
}
