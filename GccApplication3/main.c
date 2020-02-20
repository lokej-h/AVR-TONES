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

enum PlayStates {Playing, Menu} State;


void Tick()
{
	static Note* song;
	static int currentNote;
	static int songLen;
	switch(State)
	{
		case Playing:
			if (get_button_press() == '*')
			{
				State = Menu;
			}
			if (currentNote == songLen)
			{
				State = Menu;
			}
			break;
		case Menu:
			break;			
	}
	switch(State)
	{
		case Menu:
		{
			if (get_button_press() == '1')
			{
				DUTYCYCLE = .5;
				lcd_pos(1,0);
				lcd_puts2("Volume: HIGH");
			}
			if (get_button_press() == '2')
			{
				DUTYCYCLE = .3;
				lcd_pos(1,0);
				lcd_puts2("Volume: MID");
			}
			if (get_button_press() == '3')
			{
				DUTYCYCLE = .1;
				lcd_pos(1,0);
				lcd_puts2("Volume: LOW");
			}
			if (get_button_press() == '4')
			{
				FMOD = 100;
			}
			if (get_button_press() == '5')
			{
				FMOD = 0;
			}
			if (get_button_press() == '6')
			{
				FMOD = -100;
			}		
			do //is state change
			{
				if (get_button_press() == '0')
				{
					song = WMIH;
					lcd_pos(0,0);
					lcd_puts2("When Mom Isn't Home");
					State = Playing;
				}
				if (get_button_press() == '#')
				{
					song = BELL;
					lcd_pos(0,0);
					lcd_puts2("SchoolBells");
					State = Playing;
				}
			} while (expression);
			if (get_button_press() == '7')
			{
				TEMPO = 75;
			}	
			if (get_button_press() == '8')
			{
				TEMPO = 120;
			}
			if (get_button_press() == '9')
			{
				TEMPO = 150;
			}			
		}
		case Playing:	
		{
			PlayNote(song[currentNote]);
			currentNote++;
		}
	}
}


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

