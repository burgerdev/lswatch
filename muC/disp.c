
#include <avr/io.h>
#include <util/delay.h>


#include "globals.h"
#include "disp.h"

uint8_t disp(uint8_t i)
{
        if (i>7|| i<0)
        {
                err();
                return 0;
        }

	if (i==0)
	{
		for(uint8_t j=3;j;j--);
		{
			disp(1);
			_delay_ms(200);
			disp(2);
			_delay_ms(200);
		}
		disp(3);
		return 1;
	}

	disp_off();

        if (i & 1)
                LEDLOW_ON();
        if (i & 2)
                LEDMID_ON();
        if (i & 4)
                LEDHI_ON();

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
        int i;
                for(i=0;i<5;i++)
                {
                        LEDLOW_ON();
                        LEDMID_ON();
                        LEDHI_ON();
                        _delay_ms(100);
                        LEDLOW_OFF();
                        LEDMID_OFF();
                        LEDHI_OFF();
                        _delay_ms(100);
                }
}

