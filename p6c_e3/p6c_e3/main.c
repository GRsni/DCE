/*
 * p6c_e3.c
 *
 * Created: 10/05/2021 9:30:00
 * Author : DCE
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "ADC.h"

#define LED1 5
#define LED2 6

#define ADC_CHANNEL 0


void init_led_ports()
{
	DDRD|=(1<<DDD5)|(1<<DDD6);
}

void init_TIMER0_PWM_Phase()
{
	TCNT0=0;
	TCCR0A|=(1<<WGM00)|(1<<COM0A1)|(1<<COM0B1);
}

void start_TIMER0_PWM_Phase()
{
	TCCR0B|=(1<<CS01)|(1<<CS00);
}

void duty_TIMER0_PWM_Phase(uint8_t valueOCR0A, uint8_t valueOCR0B)
{
	OCR0A=valueOCR0A;
	OCR0B=valueOCR0B;
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

int main(void)
{
	uint8_t phase_value=128;
	
	init_led_ports();
	init_TIMER0_PWM_Phase();
	init_TIMER0_prescaler(8);
	duty_TIMER0_PWM_Phase(128, 128);
	
	switch_ADC_channel(ADC_CHANNEL, ADC_IS_POLLING);
	
	while (1)
	{
		uint16_t adc_val=read_ADC();
		phase_value=(adc_val>>2);
		duty_TIMER0_PWM_Phase(phase_value, phase_value);
	}
}



