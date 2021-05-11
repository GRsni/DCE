/*
 * robot_01_buzzer.c
 *
 * Created: 10/05/2021 10:38:32
 * Author : DCE
 */ 

#include <avr/io.h>
#include <avr/delay.h>

#define BUZZER 2


static inline init_buzzer_port()
{
	DDRB |= (1<<BUZZER);	
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		PORTB ^=(1<<BUZZER);
		_delay_ms(2);
    }
}

