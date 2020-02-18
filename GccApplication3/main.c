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

#define TRUE 1
#define FALSE 0
#define LED_ON PORTB |= (1<<PORTB0)
#define LED_OFF PORTB &= ~(1<<PORTB0)
#define LED_TOGGLE PINB |= (1<<PINB0)
#define CONVERT_TO_INT(x) (int)(x - '0')
#define CONVERT_TO_CHAR(x) (x + '0')
#define SET_LOW(p,i) p &= !(1<<i)
#define SET_HIGH(p,i) p |= (1<<i)
#define NumNotes(x) sizeof(x)/sizeof(Note)
#define SPK_ON PORTB |= 0x01;
#define SPK_OFF PORTB |= 0x00;

#define A 1136
#define As 1073
#define B 1012
#define C 956
#define Cs 902
#define D 851
#define Ds 804
#define E 758
#define F 716
#define Fs 676
#define G 638
#define Gs 602

#define TEMPO 100000ul
#define W 1.0
#define H .5
#define Q .25
#define Ei .125
#define S .0625

typedef struct {
	int sec ;
	int min ;
	int hour;
	int day ;
	int month;
	int year ;
	// int am ;
}current_time;


typedef struct
{
	int freq, duration;
}Note;

//	  [A]  [As]  [B] [C][Cs] [D] [Ds][E] [Fs][G][Gs]
//int notes{1136,1073,1012,956,902,851,804,758,716,676,638};
Note new_song[] ={
	{C, W},
	{E, W},
	{G, W},
	{B, W},
	{G, W},
	{E, W},
	{C, W},
};

void PlayNote(Note noteIn)
{
	long int k = 10000000; // noteIn.duration/(2*noteIn.freq);
	int t = noteIn.freq; // 1/(2*noteIn.freq);
	for(int i=0; i<k; ++i)
	{
		SPK_ON;
		avr_wait_usec(t);
		SPK_ON;
		avr_wait_usec(t);
	}
}
void PlaySong(Note* songIn)
{
	for(int i=0; i<7; ++i)
	{
		PlayNote(songIn[i]);
	}
}
current_time ct;

int MILLITARY = TRUE;

/*
	Inits the time structure
*/
void init_time()
{
	ct.sec = 0;
	ct.min = 0;
	ct.hour = 0;
	ct.day = 1;
	ct.month = 1;
	ct.year = 1900;
	// ct.am = 0;
}
	



/*
	This is an instruction wait
	DO NOT USE
*/
// void wait()
// {
	// volatile long int i = 0;
	// for (int j=0; j<20; ++j)
	// {
		// ;
		// for (;i <50000;++i)
		// {
			// ;
		// }
	// }
// }

// void blink()
// {
	// LED_ON;
	// wait();
	// LED_OFF;
	// wait();
// }

void timeTick()
{
	ct.sec++;
	if(ct.sec>=60)
	{
		ct.min++;
		ct.sec=0;
		if(ct.min>=60)
		{
			ct.hour++;
			ct.min=0;
			if(ct.hour>=24)
			{
				ct.hour = 0;
				if(ct.day==28 && ct.month ==2 && ((ct.year%4)!=0 || (ct.year%100)==0) && (ct.year%400)!=0)
				{
					ct.day=1;
					ct.month++;
				}
				else if(ct.day==29 && ct.month ==2 && (ct.year%4)==0 && ((ct.year%100)!=0 || (ct.year%400)==0))
				{
					ct.day=1;
					ct.month++;
				}
				else if(ct.day==30 && (ct.month==4 || ct.month==6 || ct.month ==9 || ct.month==11))
				{
					ct.day=1;
					ct.month++;
				}
				else if(ct.day==31 && (ct.month==1 || ct.month==3 || ct.month ==5 || ct.month==7 || ct.month==8 || ct.month==10 || ct.month==12))
				{
					ct.day=1;
					ct.month++;
				}
				else
				{
					ct.day++;
					return;
				}
				
				if(ct.month>=13)
				{
					ct.year++;
					ct.month=1;
				}			
			}
		}
	}
}

char* get_date_as_str(char* date)
{
	//char date[15];
	sprintf(date, "%02d/%02d/%04d", ct.month, ct.day, ct.year);
	return date;
}

char* get_time_as_military_str(char* time)
{
	//char time[15];
	sprintf(time, "%02d:%02d:%02d", ct.hour, ct.min, ct.sec);
	return time;
}

char* get_time_as_str(char* time)
{
	//char time[15];
	int hour = ct.hour % 12;
	char* m;
	if (ct.hour > 11 && ct.hour < 24)
	{
		m = "pm";
	}
	else
	{
		m = "am";
	}
	if (hour == 0) 
	{
		hour = 12;
	}
	sprintf(time, "%02d:%02d:%02d%s", hour, ct.min, ct.sec, m);
	return time;
}

void update_seconds()
{
	lcd_pos(1,6);
	lcd_put(CONVERT_TO_INT(ct.sec/10));
	lcd_pos(1,7);
	lcd_put(CONVERT_TO_INT(ct.sec%10));
}

inline void colon_off()
{
	lcd_pos(1,2);
	lcd_put(' ');
	lcd_pos(1,5);
	lcd_put(' ');
}

inline void colon_on()
{
	lcd_pos(1,2);
	lcd_put(':');
	lcd_pos(1,5);
	lcd_put(':');
}

void lcd_write_time()
{
	char date[15];
	char time[15];
	lcd_clr();
	lcd_pos(0,0);
	lcd_puts2(get_date_as_str(date));
	lcd_pos(1,0);
	if (MILLITARY)
	{
		lcd_puts2(get_time_as_military_str(time));
	}
	else 
	{
		lcd_puts2(get_time_as_str(time));
	}
	if (ct.sec%2) // if odd/even
	{
		colon_off();
	}
	else
	{
		colon_on();
	}
}	


void js_test()
{
	lcd_init();
	lcd_clr();
	lcd_pos(0,0);
	lcd_puts2("fish");
	init_time();
	
	while(1)
	{
		int l;
		for (l=0;l<31;++l)
		{
			
			int k;

			for (k=0; k<24; ++k)
			{
				lcd_write_time(0);
				avr_wait(1000);
				int j;
				for (j=0; j<60; ++j)
				{
					int i=0;
					for (i=0; i<60; ++i)
					{
						timeTick();
					}
				}
				if ('*' == get_button_press())
				{
					MILLITARY = !MILLITARY;
				}
			}
		}
	}
}


void timeChange(int button)
{
	if(button ==15)
	{
		MILLITARY = !MILLITARY;
	}
	if(button == 13)
	{
		for(int i=0; i<10;i++)
		{
			if(2 == i || 5==i)
			{
				++i;
			}
			lcd_pos(0,i);
			lcd_put('_');
			avr_wait(100);
			button=0;
			while(button ==0 || button == 4 || button ==8 ||button ==12 || button == 16 || button ==13 ||button ==15 || (0==i && !(1==button || button == 14)) || (3==i && !(button <4 || button == 14)))
			{
				
				button = findWhichPin();
				if(button ==1 || button ==5 || button == 9 || button == 13 )
				{
					
					button = findWhichPin();
				}
			}
			lcd_pos(0,i);
			lcd_put(getButtonValue(button));
			switch(i)
			{
				case 0:
				ct.month=10*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 1:
				ct.month+=CONVERT_TO_INT(getButtonValue(button));
			
				break;
				case 3:
				ct.day=10*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 4:
				ct.day+=CONVERT_TO_INT(getButtonValue(button));
				break;
				case 6:
				ct.year=1000*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 7:
				ct.year+=100*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 8:
				ct.year+=10*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 9:
				ct.year+=CONVERT_TO_INT(getButtonValue(button));
				break;
			}
		
		}
	
		for(int i=0; i<8;i++)
		{
		
			if(2 == i || 5==i)
			{
				++i;
			}
			lcd_pos(1,i);
			lcd_put('_');
			avr_wait(100);
			button=0;
			//while(button ==0 && ((0 == i || 3 == i || 6 == i) && getButtonValue(button) <6'))
		
			while(button ==0 || button == 4 || button ==8 ||button ==12 || button == 16 || button ==13 ||button ==15 ||(i==0 && (button > 2 && !(14==button))) ||((i==3 || i==6) && 7<button ))
			{
				button = findWhichPin();
			}
			lcd_pos(1,i);
			lcd_put(getButtonValue(button));
			switch(i)
			{
				case 0:
			
				ct.hour=10*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 1:
				ct.hour+=CONVERT_TO_INT(getButtonValue(button));
				break;
				case 3:
				ct.min=10*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 4:
				ct.min+=CONVERT_TO_INT(getButtonValue(button));
				break;
				case 6:
				ct.sec=10*CONVERT_TO_INT(getButtonValue(button));
				break;
				case 7:
				ct.sec+=CONVERT_TO_INT(getButtonValue(button));
				break;
			}
		}
	
	}
}
	
	//	  [A]  [As]  [B] [C][Cs] [D] [Ds][E] [Fs][G][Gs]
//int notes{1136,1073,1012,956,902,851,804,758,716,676,638};
	//	  [A]  [As]  [B] [C][Cs] [D] [Ds][E] [Fs][G][Gs]
//int notes{1136,1073,1012,956,902,851,804,758,716,676,638};

void note_test(int note)
{
	PORTB=0x01;
	avr_wait_usec(note);
	PORTB=0x00;
	avr_wait_usec(note);
}


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
		//note_test(Fs);
		PlaySong(new_song);
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

