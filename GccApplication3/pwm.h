/*
 * pwm.h
 *
 * Created: 2/19/2020 7:27:48 AM
 *  Author: willi
 */ 

#define PWM_PIN_ON PORTB |= 0x01;
#define PWM_PIN_OFF PORTB |= 0x00;

#ifndef PWM_H_
#define PWM_H_
int t;
void pwd_pulse(int dutyCycle, int periodUs)
{
	assert dutyCycle<=100;
	t=periodUs*dutyCycle/100;
	PWM_PIN_ON;
	avr_wait_usec(t);
	PWM_PIN_OFF;
	avr_wait_usec(periodUs-t);
}
int d;
void pwm_signal(int dutyCycle, int periodUs, int duration)
{
	for(d=0; d<duration/periodUs; ++d)
	{	
		pwd_pulse(dutyCycle,periodUs);	
	}
}



#endif /* PWM_H_ */