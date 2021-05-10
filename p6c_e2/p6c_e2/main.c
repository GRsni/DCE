/*
* p6c_e2.c
*
* Created: 10/05/2021 9:06:43
* Author : DCE
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/delay.h>

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
	uint8_t going_up=1;
	uint8_t f=128;
	
	init_led_ports();
	init_TIMER0_PWM_Phase();
	init_TIMER0_prescaler(8);
	duty_TIMER0_PWM_Phase(128, 128);
	while (1)
	{
		if(going_up)
		{
			f++;
			duty_TIMER0_PWM_Phase(f, f);
			_delay_ms(50);
			if(f>=255)
			{
				going_up=0;
			}
		}
		else
		{
			f--;
			duty_TIMER0_PWM_Phase(f, f);
			_delay_ms(10);
			if(f<=0)
			{
			going_up=1;
			}
		}
	}
}

