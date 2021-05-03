/*
* TIMER0.c
*
* Created: 26/04/2021 9:55:20
*  Author: DCE
*/

#include <avr/io.h>

#include "TIMER.h"

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

void set_TIMER0_ms(uint16_t ms, uint8_t *ticks, uint8_t *remainder)
{
	
}

void init_TIMER1_INT()
{
	TIMSK1 |= (1<<OCIE1A);
	TCNT1=0;
}

void init_TIMER1_polling()
{
	TCCR1B |= (1<<CS10);
	TCNT1 = 0;
}

void init_TIMER1_prescaler(uint16_t prescaler)
{
	switch(prescaler)
	{
		case 0:
		TCCR1B|=(1<<CS10);
		break;
		case 8:
		TCCR1B|=(1<<CS11);
		break;
		case 64:
		TCCR1B|=(1<<CS11)|(1<<CS10);
		break;
		case 256:
		TCCR1B|=(1<<CS12);
		break;
		case 1024:
		TCCR1B|=(1<<CS12)|(1<<CS10);
		break;
		default:
		break;
	}

}


void set_TIMER1_value(uint16_t value)
{
	OCR1AH=(value>>8);
	OCR1AL=(value);
}

void set_TIMER1_ms(uint16_t ms, uint8_t *ticks, uint8_t *remainder)
{
	
}

void set_TIMER1_CTC_mode(CTC_MODE_t mode)
{
	switch(mode){
		case TOGGLE:
		TCCR1A |= (1<<COM1A0);
		break;
		case CLEAR:
		TCCR1A |= (1<<COM1A1);
		break;
		case SET:
		TCCR1A |= (1<<COM1A1)|(1<<COM1A0);
		break;
	}
}

void set_TIMER1_CTC_comp_value(uint16_t value)
{
	
}

void set_TIMER1_CTC_start()
{
	TCCR1B|=(1<<WGM12);
}