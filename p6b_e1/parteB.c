/*
 * p6b_e1.c
 *
 * Created: 26/04/2021 12:24:40
 * Author : DCE
 */ 

#define  F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>

#include "TIMER.h"
#include "LED.h"

#define LED 5
#define CTC 1	

void init_LED_ports();

ISR(TIMER1_COMPA_vect)
{
	led_blink(LED);	
}

int main(void)
{
    init_LED_ports();
	init_TIMER1_INT();
	//set_TIMER1_CTC_mode(TOGGLE);
	init_TIMER1_prescaler(1024);
	set_TIMER1_value(7812);
	set_TIMER1_CTC_start();
	
	sei();
	
    while (1) 
    {
    }
}

void init_LED_ports(){
	DDRB |= (1<<LED);
}

