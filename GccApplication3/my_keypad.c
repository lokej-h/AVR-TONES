#include "avr.h"
#include "lcd.h"
#include "my_lcd.h"


int get_row()
{
	DDRC	= 0xF0;		// setup rows for w1 and cols for 0
	PORTC	= 0x0F;		// cols as 0 and rows as w1
	unsigned int pinstate = (PINC & 0x0F);
	unsigned int row;
	if (pinstate) // if any button pressed
	{
		for (row = 0; row <= 4; ++row)
		{
			if ((pinstate<<row) & 0x08)
			{
				return row;
			}
		}
	}
	return -1;
}

int get_col()
{
	DDRC	= 0x0F;		// setup cols for w1 and rows for 0
	PORTC	= 0xF0;		// cols as w1 and rows as 0
	unsigned int pinstate = (PINC & 0xF0);
	unsigned int col;
	if (pinstate) // if any button pressed
	{
		for (col = 0; col <= 4; ++col)
		{
			if ((pinstate<<col) & 0x80)
			{
				return col;
			}
		}
	}
	return -1;
}

unsigned char is_pressed(unsigned char r, unsigned char c)
{
	//		KEYPAD
	//c0 c1 c2 c3 r0 r1 r2 r3
	//c7 c6 c5 c4|c3 c2 c1 c0
	//		CHIP
	//return PINC & (1<<r | 1<<c);
	DDRC	= 0xF0;		// setup rows for w1 and col for 0
	PORTC	= 0x0F;		// cols as 0 and rows as w1
	//set pin @ col c to low
	// DDRC |= (0x80 >> c);
	// PORTC &= !(0x08 >> c);
	// set pin @ row r to w1
	// PORTC |= (0x08 >> r);
	

				
	// if the pin @ row r is 0
	// i.e. PINC & (0x08 >> r) is 0
	if(!(PINC & (0x08 >> r)))
	{
		return 1;
	}
	return 0;
}


char getButtonValue(int buttonIn)
{
	switch(buttonIn)
	{
		case 1:
		return '1';
		break;
		case 2:
		return '2';
		break;
		case 3:
		return '3';
		break;
		case 4:
		return 'A';
		break;
		case 5:
		return '4';
		break;
		case 6:
		return '5';
		break;
		case 7:
		return '6';
		break;
		case 8:
		return 'B';
		break;
		case 9:
		return '7';
		break;
		case 10:
		return '8';
		break;
		case 11:
		return '9';
		break;
		case 12:
		return 'C';
		break;
		case 13:
		return '*';
		break;
		case 14:
		return '0';
		break;
		case 15:
		return '#';
		break;
		case 16:
		return 'D';
		break;
		default:
		return 'X';
		break;
		
	}
}

unsigned char findWhichPin()
{
	// avr_wait(250);
	int row = get_row();
	int col = get_col();
	if (row != -1 && col != -1)
	{
		// wait until button up
		while (get_row() != -1 && get_col() != -1) {}
		return ((row*4)+col+1);
	}
	return 0;
}

char get_button_press()
{
	int button = 0;
	button = findWhichPin();
	return getButtonValue(button);
}


void button_test()
{
	lcd_init();
	lcd_clr();
	lcd_pos(0,0);
	while(1)
	{
		char press = get_button_press();
		if ('X' != press)
		{
			lcd_put(press);
			avr_wait(1000);
		}
	}
}