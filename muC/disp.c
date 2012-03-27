
#include <avr/io.h>
#include <util/delay.h>


#include "globals.h"
#include "disp.h"
#include "lcd-routines.h"

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

void disp_off()
{
	LEDLOW_OFF();
	LEDMID_OFF();
	LEDHI_OFF();
}

void err()
{
	lcd_clear();
	lcd_string("Error!");
}

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
