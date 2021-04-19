/*
 * p5_e2.c
 *
 * Created: 12/04/2021 9:46:21
 * Author : DCE
 */ 

#define F_CPU 16000000
#define FOSC 16000000

#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>

#define LED0 0

static inline void initADC();
static inline void initPorts();
static inline void enableINT();

volatile static uint16_t value;

ISR(ADC_vect){
	value=ADC;
}


int main(){
	
	initADC();
	initPorts();
	sei();
	
	while(1){
		enableINT();
		if(value<750){
			PORTB|=(1<<LED0);
			}else{
			PORTB&=~(1<<LED0);
		}
	}
	_delay_ms(300);
}

static inline void initADC(){
	ADMUX|=(1<<MUX0)|(1<<REFS0);
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

static inline void enableINT(){
	ADCSRA|=(1<<ADSC);
}


static inline void initPorts(){
	DDRB|=(1<<LED0);
}
