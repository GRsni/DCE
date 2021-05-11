/*
 * TIMER0.c
 *
 * Created: 26/04/2021 9:55:20
 *  Author: DCE
 */ 

#include <avr/io.h>

#include "TIMER0.h"

void init_TIMER0_INT()
{
	TIMSK0 |= (1<<TOIE0);
}

void init_TIMER0_polling()
{
	TCCR0B |= (1<<CS00);
	TCNT0 = 0;
}

void init_TIMER0_prescaler(uint16_t prescaler)
{
	switch(prescaler)
	{
		case 0:
		TCCR0B|=(1<<CS00);
		break;
		case 8:
		TCCR0B|=(1<<CS01);
		break;
		case 64:
		TCCR0B|=(1<<CS01)|(1<<CS00);
		break;
		case 256:
		TCCR0B|=(1<<CS02);
		break;
		case 1024:
		TCCR0B|=(1<<CS02)|(1<<CS00);
		break;
		default:
		break;
	}

}


void set_TIMER0_value(uint8_t value)
{
	TCNT0=value;
}