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

/*
 * This file provides routines for LC display management
 */

// display time, treat integer as 1/100s 
uint8_t disp(uint32_t n);

// display percentage 
uint8_t disp_percent(uint32_t i);

// display string
uint8_t disp_str(uint8_t *c);

// display error message
void err(void);

// convert integer to string, treat integer as percentage
uint8_t itoa(uint32_t i, uint8_t *data);
