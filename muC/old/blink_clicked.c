 
#define F_CPU 4000000UL
//#define F_CPU 3686400UL


#include <avr/io.h>          
#include <avr/interrupt.h>
#include <util/delay.h> 

// prescaler is 1024
#define TIMER1_PRESCALER ((1<<CS12) | (1<<CS10))


#define TIMER1_COMPARE_VALUE 36 //10ms
//#define TIMER1_COMPARE_VALUE 0xe10 //1s
//#define TIMER1_COMPARE_VALUE 0x8ca0 //10s
//#define TIMER1_COMPARE_VALUE 0xe4e1 //15s

// how to set LED
#define LEDPORT PORTB
#define LEDBIT PB5


// time_cs is centiseconds, 100cs == 1s

// accessories
uint8_t button_clicked();
void showtime();
void blink(uint8_t n);
uint8_t switchOn();
void loop_main();
void loop_main_test();

// timer functions high level
void reset();
void start();
void stop();

// timer functions low-level
void timer_inc();


// global time variables
volatile uint8_t time_h;
volatile uint8_t time_m;
volatile uint8_t time_s;
volatile uint8_t time_cs;
uint8_t is_started;

void main()
{
	cli();

	// B is output
	DDRB = 0xFF;
	PORTB = 0x00;

	// C is input
	DDRC = 0x00;
	PORTC = 0xFF;
		
	
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
		loop_main();
		//loop_main_test();
		//blink(1);
	}
}

// heart-beat function, increments the clock by 100th second
ISR(TIMER1_CAPT_vect)
{
	// disable interrupts in this function
	cli();

	timer_inc();

	// enable interrupts
	sei();
}

void showtime()
{
	// ignore h,m - only show seconds and 10ths
	blink(time_s);
	_delay_ms(2000);
	blink(time_cs/10);
}

void blink(uint8_t n)
{
	while (n--)
	{
		LEDPORT |= 1<<LEDBIT;
		_delay_ms(200);
		LEDPORT &= ~(1<<LEDBIT);
		_delay_ms(200);
	}
}

uint8_t button_clicked()
{
	uint8_t r = 0;

	if (!switchOn())
	{
		while (!switchOn());
		r = 1;
	}
	return r;

}

uint8_t switchOn()
{
	unsigned char r = 0;
	
	if ( (PINC & 1<<PC5) == 1<<PC5 )
	{
		_delay_ms(10);
		if ( (PINC & 1<<PC5) == 1<<PC5 )
			r = 1;
	}

	return r;
}

void loop_main()
{
	if (button_clicked())
	{
		if (is_started)
			stop();
		else
			start();
	}
}

void loop_main_test()
{
	if (button_clicked())
		blink(5);
}

void start()
{
	reset();
	is_started = 1;
}

void stop()
{
	cli();
	is_started = 0;
	_delay_ms(3000);
	showtime();
	sei();
}

void reset()
{
	cli();
	time_h = 0;
	time_m = 0;
	time_s = 0;
	time_cs = 0;
	sei();
}

void timer_inc_h()
{
	time_h++;
	// error handling ommitted for PoC
}

void timer_inc_m()
{
	time_m++;
	if (time_m == 60)
	{
		time_m = 0;
		timer_inc_h();
	}
}

void timer_inc_s()
{
	time_s++;
	if (time_s == 60)
	{
		time_s = 0;
		timer_inc_m();
	}
}

void timer_inc_cs()
{
	time_cs++;
	if (time_cs == 100)
	{
		time_cs = 0;
		timer_inc_s();
	}
}

void timer_inc()
{
	timer_inc_cs();
}

