
// is the light barrier broken?
// this needs to be called at least every 1ms to make
// sure that no break is missed
uint8_t broken(void);

// amount of time that can be watied after one crossing in ms
// a trade-off between start stop interval length and double
// registration avoidance is done here
#define LS_WAIT_TIME_MS 1000