#define F_CPU 4000000UL


#define LEDLOW_ON() PORTB |= 1<<PB0
#define LEDLOW_OFF() PORTB &= ~(1<<PB0)


#define LEDMID_ON() PORTB |= 1<<PB1
#define LEDMID_OFF() PORTB &= ~(1<<PB1)

#define LEDHI_ON() PORTB |= 1<<PB2
#define LEDHI_OFF() PORTB &= ~(1<<PB2)

