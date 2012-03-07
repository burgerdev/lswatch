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

