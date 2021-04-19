/*
 * p5_e3.c
 *
 * Created: 12/04/2021 9:15:46
 * Author : DCE
 */ 
#define F_CPU 16000000
#define FOSC 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED0 0
#define BUTTON 2

static inline void initADC();
static inline void initPorts();
static inline void initINT0();
static inline void enableINT();

volatile static uint16_t value;
volatile static uint16_t threshold=512;

ISR(ADC_vect){
	value=ADC;
}

ISR(INT0_vect){
	threshold+=10;
	if(threshold>1024){
		threshold=512;
	}
}


int main(){
	
	initADC();
	initPorts();
	initINT0();
	sei();
	
	while(1){
		enableINT();
		if(value>threshold){
			PORTB|=(1<<LED0);
			}else{
			PORTB&=~(1<<LED0);
		}
	}
	_delay_ms(300);
}

static inline void initADC(){
	ADMUX|=(1<<MUX1)|(1<<MUX0)|(1<<REFS0);
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

static inline void enableINT(){
	ADCSRA|=(1<<ADSC);
}

static inline void initINT0(){
	EICRA|=(1<<ISC01);// INT0-Falling edge
	EIMSK|=(1<<INT0);// Enable INT0;
}

static inline void initPorts(){
	DDRB|=(1<<LED0);
	PORTD|=(1<<BUTTON);
}

