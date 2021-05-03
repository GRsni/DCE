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
#include "ADC.h"

#define LED 5
#define ADC_LED 0
#define POT_CHANNEL 0

volatile uint16_t adc_value=0;

void init_ports();

ISR(TIMER1_COMPA_vect)
{
	led_blink(LED);
	//switch_ADC_channel(POT_CHANNEL, ADC_INTERRUPT);
}

ISR(ADC_vect)
{
	adc_value=ADC;
	zero_ADC();
}

int main(void)
{
	init_ports();
	//switch_ADC_channel(POT_CHANNEL, ADC_INTERRUPT);
	
	init_TIMER1_INT();
	
	set_TIMER1_value(7812);
	set_TIMER1_CTC_start();
	init_TIMER1_prescaler(1024);
	
	sei();
	
	while (1)
	{
		if(adc_value>512)
		{
			//led_on(ADC_LED);
		}else
		{
			led_off(ADC_LED);			
		}
	}
}

void init_ports(){
	DDRB |= (1<<LED)|(1<<ADC_LED);
}

