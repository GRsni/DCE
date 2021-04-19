/*
 * p5b_e1.c
 *
 * Created: 12/04/2021 12:18:42
 * Author : DCE
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "ADC.h"
#include "USART.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 //103 cycles system-clk

#define LED_POT 1
#define POT_CHANNEL 0

static inline void initPorts();
static inline void led_on(uint8_t pin);
static inline void led_off(uint8_t pin);


int main(void)
{
	initADC_Polling();
	USART_Init(MYUBRR);
	initPorts();
	switch_ADC_channel(0, true);
    /* Replace with your application code */
    while (1) 
    {
		if(readADC()>512){
			led_on(LED_POT);
		}else{
			led_off(LED_POT);
		}
				
    }
}

static inline void initPorts(){
	DDRB|=(1<<LED_POT);
}

static inline void led_on(uint8_t pin){
	PORTB|=(1<<pin);
}

static inline void led_off(uint8_t pin){
	PORTB&=~(1<<pin);
}

