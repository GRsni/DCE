/*
* p6_e2.c
*
* Created: 26/04/2021 11:18:24
* Author : DCE
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>

#include "TIMER.h"
#include "LED.h"

#define LED 2

void init_LED_ports();

static volatile uint16_t overflow_count=0;
static uint16_t timer_remainder=65386-20;

ISR(TIMER1_OVF_vect){
	if(overflow_count>=16)
	{
		led_blink(LED);
		overflow_count=0;
	}
	else
	{
		if(overflow_count==15)
		{
			set_TIMER1_value(timer_remainder);
		}
		overflow_count++;
	}
}

int main(void)
{
	init_LED_ports(PORTB, LED);
	init_TIMER1_INT();
	init_TIMER1_prescaler(8);
	set_TIMER1_value(0);
	sei();
	while (1)
	{
	}
}

void init_LED_ports()
{
	DDRB |= (1<<LED);
}

