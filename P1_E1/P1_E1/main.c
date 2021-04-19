/*
 * P1_E1.c
 *
 * Created: 12/04/2021 8:50:29
 * Author : DCE
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void){
	//--SETUP------------//
	DDRD |= (1<<DDD1); //Set LED 1 pin of PORTB as output pin
	
	//--LOOP------------//
	while(1)//Blink PORTB infinitely
	{
		PORTD |= (1<<PORTD1);
		_delay_ms(500);//Delay of 500 milli-seconds
		PORTD &= ~(1<<PORTD1);
		_delay_ms(500);
	}
}

