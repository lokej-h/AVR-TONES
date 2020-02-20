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
//char buttonPressed=0;

void Tick()
{
	static Note* song;
	static int currentNote;
	static int songLen;
	
	char buttonPressed = get_button_press();
	switch(State)
	{
		case Playing:
		{
			if (buttonPressed == '*')
			{
				State = Menu;
			}
			else if (currentNote == songLen)
			{
				State = Menu;
			}
			//else continue to play
			else
			{
				PlayNote(song[currentNote]);
				currentNote++;
			}
			break;
		}
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
				lcd_puts2("Volume: MID ");
			}
			else if (buttonPressed == '3')
			{
				DUTYCYCLE = .1;
				lcd_pos(1,0);
				lcd_puts2("Volume: LOW ");
			}
			else if (buttonPressed == '4')
			{
				FMOD = 100;
				lcd_pos(3,0);
				lcd_puts2("Pitch: LOW  ");
			}
			else if (buttonPressed == '5')
			{
				FMOD = 0;
				lcd_pos(3,0);
				lcd_puts2("Pitch: NORM");
			}
			else if (buttonPressed == '6')
			{
				FMOD = -100;
				lcd_pos(3,0);
				lcd_puts2("Pitch: HIGH");
			}
			else if (buttonPressed == '0')
				{
					song = SHEEP;
					lcd_pos(0,0);
					lcd_puts2("Sheep Song  ");
					songLen = 21;
					currentNote = 0;
					State = Playing;
				}
			else if (buttonPressed == '#')
				{
					song = BELL;
					lcd_pos(0,0);
					lcd_puts2("School Bells       ");
					songLen = 18;
					currentNote = 0;
					State = Playing;
				}
			else if (buttonPressed == '7')
			{
				TEMPO = 75;
				lcd_pos(4,0);
				lcd_puts2("Tempo: SLOW  ");
			}
			else if (buttonPressed == '8')
			{
				TEMPO = 120;
				lcd_pos(4,0);
				lcd_puts2("Tempo: NORM   ");
			}
			else if (buttonPressed == '9')
			{
				TEMPO = 210;
				lcd_pos(4,0);
				lcd_puts2("Tempo: FAST   ");
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
		// PlaySong(new_song);
		// avr_wait(1000);
		// note_test(C4);
		//button_test();
	}
}

