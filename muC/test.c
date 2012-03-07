 
#include "globals.h"

#include <avr/io.h>          
#include <avr/interrupt.h>
#include <util/delay.h> 

#include "disp.h"
#include "timer.h"

// prescaler is 1024
#define TIMER1_PRESCALER ((1<<CS12) | (1<<CS10))


#define TIMER1_COMPARE_VALUE 36 //10ms
//#define TIMER1_COMPARE_VALUE 0xe10 //1s
//#define TIMER1_COMPARE_VALUE 0x8ca0 //10s
//#define TIMER1_COMPARE_VALUE 0xe4e1 //15s

// how to set LED
#define LEDPORT PORTB
#define LEDBIT PB5


void SWAP_STATE()
{	
	if (PORTC & 1<<PC1 == 1<<PC1)
	       PORTC &= ~(1<<PC1);
	else	
		PORTC |= 1<<PC1;
}

uint8_t SAME()
{
	uint8_t ans = 0;
	ans = PINC & 1<<PC0 | PORTC & 1<<PC1;

	if (ans & ((1<<PC0) | (1<<PC1)) == (1<<PC0)|(1<<PC1)  || ans == 0)
		ans = 1;
	else
		ans = 0;
	return ans;

}


uint16_t getADC(uint16_t n);



void loop_main_LED()
{
	uint16_t n = 0;
	uint16_t result=0;
	while (1)
	{
		n++;
		result = 0;

		PORTC &= ~(1<<PC1);

		_delay_ms(500);
		
		PORTC |= 1<<PC1;
		
		start();
		int id=0;
		while ((result = getADC(4)/128) < 6) id++;
		stop();

		//disp(time_cs / 20);
		//disp(id>5?7:1);
		disp( (uint8_t) id);

		_delay_ms(1000);
		disp_off();
		_delay_ms(100);
		

	}
}

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

// time_cs is centiseconds, 100cs == 1s

// accessories
void loop_main();




void main()
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
	PORTD = ~(1<<PD7);
	
	// init ADC
	ADMUX = 1<<REFS0;
	ADCSRA = 1<<ADEN;
	
	

	// set timer management
	TIMSK |= (1<<TICIE1);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | TIMER1_PRESCALER;
	ICR1H = TIMER1_COMPARE_VALUE >> 8;
	ICR1L = TIMER1_COMPARE_VALUE & 0xFF;

	// initialize flag
	is_started = 0;

	// enable interrupts, start loop
	sei();
	while (1)
	{
		//loop_main();
		//loop_main_test();
		loop_main_LED();
		//blink(1);
	}
}






