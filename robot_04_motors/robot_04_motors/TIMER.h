/*
* TIMER.h
*
* Created: 24/05/2021 11:50:38
*  Author: DCE
*/

#include <avr/io.h>

#ifndef TIMER_H
#define TIMER_H

static inline void init_TIMER0_CTC()
{
	TCCR0A |= (1<<COM0A0)|(1<<WGM01);		//Enable timer0 CTC Toggle on compare match
	TCCR0B |= (1<<CS02);					//Prescaler = 256 => 16us per cycle
	TIMSK0 |= (1<<OCIE0A);					//Enable compare match A interrupt handle
	TCNT0 = 0;
}

static inline void duty_TIMER0_Phase(uint8_t value)
{
	OCR0A = value;
}

static inline void start_TIMER0_CTC()
{
	TCNT0 = 0;
	TIMSK0 |= (1<<OCIE0A);					//Enable compare match A interrupt handle
}

static inline void init_TIMER1_CTC()
{
	TCCR1A |= (1<<COM1A0)|(1<<WGM12);	//Enable timer1 CTC Toggle on compare match
	TCCR1B |= (1<<CS12)|(1<<CS10);		//Prescaler = 1024 => 64us per cycle
	TIMSK1 |= (1<<OCIE1A);				//Enable compare match A interrupt handle
	TCNT1 = 0;
}

static inline void duty_TIMER1_Phase(uint16_t value)
{
	OCR1A = value;
}

static inline void start_TIMER1_CTC()
{
	TCNT1 = 0;
	TIMSK1 |= (1<<OCIE1A);				//Enable compare match A interrupt handle
}

static inline void init_TIMER4A_PWM_Phase()
{
	TCCR4A|=(1<<PWM4A)|(1<<COM4A0);
}

static inline void init_TIMER4D_PWM_Phase()
{
	TCCR4C |= (1<<PWM4D)|(1<<COM4D1);
}

static inline void init_TIMER4_freq_div()
{
	TCCR4B |= (1<<CS42)|(1<<CS41)|(1<<CS40);
}

static inline void init_TIMER4_WFG_mode()
{
	TCCR4D |= (1<<WGM40);
}

static inline void start_TIMER4_PWM_Phase()
{
	TCNT4=0;
}

static inline void duty_TIMER4A_PWM_Phase(uint8_t valueOCR0A)
{
	OCR4A = 255 - valueOCR0A;
}

static inline void duty_TIMER4D_PWM_Phase(uint8_t valueOCR4D)
{
	OCR4D = valueOCR4D;
}

#endif //TIMER_H