/*
 * GccApplication2.c
 *
 * Created: 1/17/2020 9:19:13 AM
 * Author : willi
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "avr.h"
#include "lcd.h"
#include "my_lcd.h"
#include "my_keypad.h"
#include "lcd_time.h"
#include "music.h"

#define TRUE 1
#define FALSE 0
// #define LED_ON PORTB |= (1<<PORTB0)
// #define LED_OFF PORTB &= ~(1<<PORTB0)
// #define LED_TOGGLE PINB |= (1<<PINB0)
#define SET_LOW(p,i) p &= !(1<<i)
#define SET_HIGH(p,i) p |= (1<<i)



int main(void)
{
	//0 for output, 1 for input
	DDRC = 0x00;
	PORTC = 0x00;
	
	// lcd inits
	init_time();
	lcd_init();
	lcd_clr();
	lcd_pos(0,0);
	lcd_write_time();
	SPK_INIT;
	
    while (1) 
    {
		Note a = {D4, W};
		//PlayNote(a);
		PlaySong(BELL);
		avr_wait(1000);
	}
}

