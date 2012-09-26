// timer functions high level
void reset(void);
void start(void);
void stop(void);


void timer_setup(void);

// has to be called before reading time_s and higher
void timer_add(void);


// global time variables
volatile uint16_t time_h;
volatile uint16_t time_m;
volatile uint16_t time_s;
volatile uint32_t time_ms;

uint8_t is_started;


/* a bit of theory:
 *
 * got CPU frequency of 3579000
 * with a prescaler of 1 that is 3579000 clock ticks per second
 * i.e. 3579 ticks per 10^-3 seconds
 * our lowest timer variable is therefore 10^-3 seconds and is
 * incremented every 36 ticks
 */

// prescaler is 1024
#define TIMER1_PRESCALER ((1<<CS10))
#define TIMER1_COMPARE_VALUE 3579

// factor from lowest variable to ms
#define TIMER1_LOWEST_IN_MS 1


/* OLDER VERSION FOR 3.6864MHz quartz
 *
 * a bit of theory:
 * 
 * got CPU frequency of 3686400
 * with a prescaler of 1024 that is 3600 clock ticks per second
 * i.e. 36 ticks per 10^-2 seconds
 * our lowest timer variable is therefore 10^-2 seconds and is
 * incremented every 36 ticks


// prescaler is 1024
#define TIMER1_PRESCALER ((1<<CS12) | (1<<CS10))
#define TIMER1_COMPARE_VALUE 36

// factor from lowest variable to ms
#define TIMER1_LOWEST_IN_MS 10

*/
