
// is the light barrier broken?
// this needs to be called at least every 1ms to make
// sure that no break is missed
uint8_t broken(void);

// assure that it was a real break
uint8_t broken_again(void);

// amount of time that can be watied after one crossing in ms
// a trade-off between start stop interval length and double
// registration avoidance is done here
#define LS_WAIT_TIME_MS 1000

// one call to getADC takes 2.1ms with prescaler 128 at 4MHz
// number of times the ADC is called
#define LS_N_ADC 2
// number of times ADC must be greater than threshold to count as broken
#define LS_N_HI 2
// threshold
#define LS_THRESH 900
// averages ADC
#define LS_ADC_AVG 16