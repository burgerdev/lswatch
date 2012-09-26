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
#include "disp.h"
#include "lcd-routines.h"


// display time, treat integer as time in 1/100s
uint8_t disp(uint32_t i)
{
	lcd_clear();
	lcd_command(LCD_SET_DDADR + 7);
	lcd_data_s('s');

	uint8_t data[8];
	uint8_t n = itoa(i, data);

	for (uint8_t i=0;i<n;i++) lcd_data_s(data[i]);
	
	return 1;
}

// display percentage 
uint8_t disp_percent(uint32_t i)
{
	lcd_clear();
	lcd_command(LCD_SET_DDADR + 7);
	lcd_data_s('%');
	
	uint8_t data[8];
	uint8_t n = itoa(i, data);
	
	for (uint8_t i=0;i<n;i++) lcd_data_s(data[i]);
	
	return 1;
}

// display string
uint8_t disp_str(uint8_t *c)
{
	lcd_clear();

	uint8_t n = 0;
	while (c[n])
	{
		lcd_data(c[n]);
		n++;
	}

	return 1;
}

// display error message
void err()
{
	lcd_clear();
	lcd_string("Error!");
}

// convert integer to string, treat integer as percentage
uint8_t itoa(uint32_t i, uint8_t *data)
{
	uint8_t def = '0';
	uint8_t n = 0;

	data[0] = def;
	data[1] = def;
	data[2] = '.';
	data[3] = def;

	while(i>0 && n<7)
	{
		data[n] = '0' + i%10;
		i = i/10;
		n++;
		if (n==2) n++;
	}


	if (n<4)
		n = 4;

	return n;

}
