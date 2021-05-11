/*
* Test_buzzer.c
* 
* Programa de control de altavoz de robot 2WD MiniQ
*
* Created: 10/05/2021 11:28:14
*  Author: Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#define BUZZER 2
#define SOUND_INTERVAL_S 2


static inline void init_buzzer_port()
{
	DDRB |= (1<<BUZZER);
}

int main(void)
{
	uint16_t sound_interval = 200;
	uint8_t count=0;
	
	init_buzzer_port();
	while (1)
	{
		for(int i=0; i<sound_interval; i++)
		{
			PORTB ^=(1<<BUZZER);
			_delay_us(2000);
		}
		
		for(int i=0; i<sound_interval; i++)
		{
			PORTB ^=(1<<BUZZER);
			_delay_us(1500);
			
		}
		
		
		for(int i=0; i<sound_interval; i++)
		{
			PORTB ^=(1<<BUZZER);
			_delay_us(1000);
		}
		
		
		for(int i=0; i<sound_interval; i++)
		{
			PORTB ^=(1<<BUZZER);
			_delay_us(1600);
		}
		
	}
}