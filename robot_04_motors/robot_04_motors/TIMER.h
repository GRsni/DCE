/*
 * TIMER.h
 *
 * Created: 24/05/2021 11:50:38
 *  Author: DCE
 */ 

#include <avr/io.h>

#ifndef TIMER_H
#define TIMER_H

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