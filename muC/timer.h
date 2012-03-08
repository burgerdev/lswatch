// timer functions high level
void reset(void);
void start(void);
void stop(void);

// timer functions low-level
void timer_inc(void);

void timer_setup(void);


// global time variables
volatile uint8_t time_h;
volatile uint8_t time_m;
volatile uint8_t time_s;
volatile uint16_t time_ms;
volatile uint16_t time_lowest;

uint8_t is_started;


// prescaler is 1024
//#define TIMER1_PRESCALER ((1<<CS12) | (1<<CS10))
// prescaler is 1
#define TIMER1_PRESCALER (1<<CS10)
#define TIMER1_COMPARE_VALUE 3000

// increment on 10^-7s uint16
#define TIMER1_COMPARE_INCREMENT 8138
#define TIMER1_MAX 10000

//#define TIMER1_COMPARE_VALUE 36 //10ms at prescaling 1024
//#define TIMER1_COMPARE_VALUE 0xe10 //1s
//#define TIMER1_COMPARE_VALUE 0x8ca0 //10s
//#define TIMER1_COMPARE_VALUE 0xe4e1 //15s