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

#define TRUE 1
#define FALSE 0
#define LED_ON PORTB |= (1<<PORTB0)
#define LED_OFF PORTB &= ~(1<<PORTB0)
#define LED_TOGGLE PINB |= (1<<PINB0)
#define SET_LOW(p,i) p &= !(1<<i)
#define SET_HIGH(p,i) p |= (1<<i)
#define NumNotes(x) sizeof(x)/sizeof(Note)
#define SPK_ON PORTB |= 0x01;
#define SPK_OFF PORTB |= 0x00;



typedef struct
{
	int freq, duration;
}Note;



void PlayNote(Note noteIn)
{
	int k =noteIn.duration*noteIn.freq;
	int t = 1/(2*noteIn.freq);
	for(int i=0; i<k; ++i)
	{
		SPK_ON;
		small_wait(t);
		SPK_ON;
		small_wait(t);
	}
}
void PlaySong(Note* songIn)
{
	for(int i=0; i<NumNotes(songIn); ++i)
	{
		PlayNote(songIn[i]);
	}
}



	
	//	  [A]  [As]  [B] [C][Cs] [D] [Ds][E] [Fs][G][Gs]
//int notes{1136,1073,1012,956,902,851,804,758,716,676,638};


int main(void)
{
	//0 for output, 1 for input
	DDRC = 0x00;
	PORTC = 0x00;
	//DDRD |= (1<<DDD0);
	//unsigned char button=0;
	
	/*
		[1][2][3][4]
		[5][6][7][8]
		[9][10][11][12]
		[13][14][15][16]
		
		c0 c1 c2 c3 r0 r1 r2 r3
	*/
	//unsigned char i=0;
	//int i=0;
	init_time();
	lcd_init();
	lcd_clr();
	lcd_pos(0,0);
	//button_test();
	//lcd_puts2("ooooo ");
	lcd_write_time();
	DDRA=0x01;
	DDRB=0x01;
    while (1) 
    {
		PORTB=0x01;
		avr_wait(2);
		PORTB=0x00;
		avr_wait(2);
		/*if(PIND & (1<<PIND0))	//if pin 1 in port D is high
		{
			button=findWhichPin();
		}
		else
		{
			LED_OFF;
			
			timeTick();
			lcd_write_time();
			avr_wait(1000);
			int button = findWhichPin();
			if(button !=0)
			{
				timeChange(button);
			}
		}*/
	}
}

