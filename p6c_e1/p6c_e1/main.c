/*
 * p6c_e1.c
 *
 * Created: 03/05/2021 12:04:34
 * Author : DCE
 */ 

#define F_CPU 16000000L

#include <avr/io.h>

#define LED1 5
#define LED2 6

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
	init_led_ports();
	init_TIMER0_PWM_Phase();
	init_TIMER0_prescaler(8);
	duty_TIMER0_PWM_Phase(178, 178);
    while (1) 
    {
    }
}

