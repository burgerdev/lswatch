/*                                          
    LSWatch, muC software for time measurement
    Copyright (C) 2012 Markus Döring

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/gpl.
*/




// is the light barrier broken?
// this needs to be called at least every 1ms to make
// sure that no break is missed
uint8_t broken(void);

// amount of time that can be waited after one crossing in ms
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
// averages ADC (4*2.1ms is enough to register objects with length >20cm and velocity < 20m/s)
#define LS_ADC_AVG 4
