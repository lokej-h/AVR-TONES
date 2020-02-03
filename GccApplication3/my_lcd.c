#include "avr.h"
#include "lcd.h"
#include "my_lcd.h"
#define CONVERT_TO_CHAR(x) (x + '0')

void print_bin(unsigned char bin)
{
	lcd_pos(1,0);
	int i;
	for (i = 1 << 8; i > 0; i = i / 2)
	{(bin & i)? lcd_put('1'): lcd_put('0');}
	avr_wait(1000);
}

void print_int(unsigned int i)
{
	lcd_pos(0,0);
	lcd_put(CONVERT_TO_CHAR(i));
}
