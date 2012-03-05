 
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

void  LEDLOW_ON() {PORTB |= 1<<PB0;}
void LEDLOW_OFF() {PORTB &= ~(1<<PB0);}


#define LEDMID_ON() PORTB |= 1<<PB1
#define LEDMID_OFF() PORTB &= ~(1<<PB1)

#define LEDHI_ON() PORTB |= 1<<PB2
#define LEDHI_OFF() PORTB &= ~(1<<PB2)

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


void blink(uint8_t n);
void err();
void disp(uint8_t i);
uint16_t getADC(uint16_t n);



void loop_main_LED()
{
	uint16_t n = 0;
	uint16_t result=0;
	while (1)
	{
		n++;
		result = 0;

		if (n%2)
			PORTC |= 1<<PC1;
		else
			PORTC &= ~(1<<PC1);
		_delay_ms(100);
		result = getADC(256);
		result = result / 128;
		disp((uint8_t) result);
		_delay_ms(300);
		disp(0);
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
uint8_t button_clicked();
void showtime();
uint8_t switchOn();
void loop_main();
//void loop_main_test();

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

void err()
{
	int i;
		for(i=0;i<5;i++)
		{
			LEDLOW_ON();
			LEDMID_ON();
			LEDHI_ON();
			_delay_ms(100);
			LEDLOW_OFF();
			LEDMID_OFF();
			LEDHI_OFF();
			_delay_ms(100);
		}
}

void disp(uint8_t i)
{
	if (i>7)
	{
		err();
		return;
	}

	LEDLOW_OFF();
	LEDMID_OFF();
	LEDHI_OFF();

	if (i & 1)
		LEDLOW_ON();
	if (i & 2)
		LEDMID_ON();
	if (i & 4)
		LEDHI_ON();

	return;
}

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
	if (PIND & 1<<PD7)
		blink(1);


	/*
	if (button_clicked())
	{
		if (is_started)
			stop();
		else
			start();
	}
	*/
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

