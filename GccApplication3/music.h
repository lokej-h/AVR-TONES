#ifndef MUSIC
#define MUSIC

#define SPK_ON PORTB |= 0x01;
#define SPK_OFF PORTB |= 0x00;
#define NumNotes(x) sizeof(x)/sizeof(Note)

#define G3	2551
#define Gs3	2408
#define Af3	2408
#define A3	2273
#define As3	2145
#define Bf3	2145
#define B3	2025
#define C4	1911
#define Cs4	1804
#define Df4	1804
#define D4	1703
#define Ds4	1607
#define Ef4	1607
#define E4	1517
#define F4	1432
#define Fs4	1351
#define Gf4	1351
#define G4	1276
#define Gs4	1204
#define Af4	1204
#define A4	1136
#define As4	1073
#define Bf4	1073
#define B4	1012
#define C5	956
#define Cs5	902
#define Df5	902
#define D5	851
#define Ds5	804
#define Ef5	804
#define E5	758
#define F5	716
#define Fs5	676
#define Gf5	676
#define G5	638
#define Gs5	602
#define Af5	602

#define TEMPO 60
#define W 4
#define H 2
#define Q 1
#define Ei .5
#define S .25


float DUTYCYCLE = .5;

typedef struct
{
	int freq, duration;
}Note;



void PlayNote(Note noteIn)
{
	int period = 2*noteIn.freq;
	int numPeriods = ((TEMPO/60)*noteIn.duration)/period;
	int ton = period*DUTYCYCLE;
	int toff = period-ton;
	for(int i=0; i<numPeriods; ++i)
	{
		SPK_ON;
		avr_wait_usec(ton);
		SPK_OFF;
		avr_wait_usec(toff);
	}
}

void PlaySong(Note* songIn)
{
	for(int i=0; i<NumNotes(songIn); ++i)
	{
		PlayNote(songIn[i]);
	}
}


void note_test(int note)
{
    PORTB=0x01;
    avr_wait_usec(note);
    PORTB=0x00;
    avr_wait_usec(note);
}

	
	//	  [A]  [As]  [B] [C4][Cs] [D] [Ds][E] [Fs][G][Gs]
//int notes{1136,1073,1012,956,902,851,804,758,716,676,638};

Note new_song[] ={
    {C4, W},
    {E4, W},
    {G4, W},
    {B4, W},
    {G4, W},
    {E4, W},
    {C4, W},
};

Note WMIH[52] = {
	{Bf3, Ei},
	{G4, S},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{D4, Ei},
	{Ef4, Ei},
	{G4, Ei},
	{G4, Ei},
	{Ef4, Ei},
	{D4, H},
	
	{Bf3, Ei},
	{G4, S},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{D4, Ei},
	{Ef4, Ei},
	{D4, Ei},
	{Bf4, Ei},
	{A4, Ei},
	{G3, H},
	
	{Bf3, Ei},
	{G4, S},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{D4, Ei},
	{Ef4, Ei},
	{G4, Ei},
	{G4, Ei},
	{Ef4, Ei},
	{D4, H},
	
	{Bf3, Ei},
	{G4, S},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{G4, Ei},
	{D4, Ei},
	{Ef4, Ei},
	{D4, Ei},
	{Bf4, Ei},
	{A4, Ei},
	{G3, H}
};

Note BELL[] = {
	{G4, Q},
	{F4, Q},
	{E4, Q},
		
	{F4, Q},
	{E4, Q},
	{D4, Q},
	
	{E4, Q},
	{D4, Q},
	{C4, Q},
	{D4, Q},
			
	{G3, W},
	{G3, W},
	
	{G3, Q},
	{A3, Q},
	{B3, Q},
	{C4, Q}
	}

#endif // MUSIC
