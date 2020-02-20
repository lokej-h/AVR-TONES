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
int buttonPressed=0;

void Tick()
{
	static Note* song;
	static int currentNote;
	static int songLen;
	
	buttonPressed = findWhichPin();
	switch(State)
	{
		case Playing:
			if (buttonPressed == '*')
			{
				State = Menu;
			}
			else if (currentNote == songLen)
			{
				State = Menu;
			}
			//else contiune to play
			else
			{
				PlayNote(song[currentNote]);
				currentNote++;
			}
			break;
		case Menu:
		{
			
			if (buttonPressed == '1')
			{
				DUTYCYCLE = .5;
				lcd_pos(1,0);
				lcd_puts2("Volume: HIGH");
			}
			else if (buttonPressed == '2')
			{
				DUTYCYCLE = .3;
				lcd_pos(1,0);
				lcd_puts2("Volume: MID");
			}
			else if (buttonPressed == '3')
			{
				DUTYCYCLE = .1;
				lcd_pos(1,0);
				lcd_puts2("Volume: LOW");
			}
			else if (buttonPressed == '4')
			{
				FMOD = 100;
			}
			else if (buttonPressed == '5')
			{
				FMOD = 0;
			}
			else if (buttonPressed == '6')
			{
				FMOD = -100;
			}
			else if (buttonPressed == '0')
				{
					song = WMIH;
					lcd_pos(0,0);
					lcd_puts2("When Mom Isn't Home");
					State = Playing;
				}
			else if (buttonPressed == '#')
				{
					song = BELL;
					lcd_pos(0,0);
					lcd_puts2("School Bells");
					State = Playing;
				}
			else if (buttonPressed == '7')
			{
				TEMPO = 75;
			}
			else if (buttonPressed == '8')
			{
				TEMPO = 120;
			}
			else if (buttonPressed == '9')
			{
				TEMPO = 150;
			}
			break;
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
	lcd_puts2("Music Player");
	lcd_pos(1,0);
	lcd_puts2("Volume: MID");
	DUTYCYCLE = .3;
	TEMPO = 120;
	FMOD = 0;
	//lcd_write_time();
	SPK_INIT;
	State = Menu;
    while (1) 
    {
		/*
		Note a = {D4, W};
		//PlayNote(a);
		PlaySong(BELL);
		avr_wait(1000);
		*/
		
		Tick();
	}
}

