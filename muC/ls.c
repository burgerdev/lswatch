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



#include <avr/io.h>
#include <util/delay.h>

#include "globals.h"
#include "adc.h"
#include "ls.h"



uint8_t broken(void)
{
	uint8_t sum = 0;
	for(int i=0;i<LS_N_ADC;i++) sum += getADC(LS_ADC_AVG) > LS_THRESH ? 1 : 0;
	if (sum<LS_N_HI)
		return 0;
	else
		return 1;

}


