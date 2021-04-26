/*
 * p6_e1.c
 *
 * Created: 26/04/2021 9:50:06
 * Author : DCE
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "TIMER0.h"
#include "LED.h"

#define LED 2

void init_led_ports();


ISR(TIMER0_OVF_vect){
	led_blink(LED);
	set_TIMER0_value(241);
}

int main(void)
{
    /* Replace with your application code */
	init_TIMER0_INT();
	init_TIMER0_prescaler(1024);
	set_TIMER0_value(241);
	init_led_ports();
	sei();
    while (1) 
    {
    }
}


void init_led_ports()
{
	DDRB |=(1<<LED);
}
