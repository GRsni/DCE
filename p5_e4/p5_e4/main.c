/*
* p5_e4.c
*
* Created: 12/04/2021 9:54:46
* Author : DCE
*/

#define F_CPU 16000000
#define FOSC 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_START 0
#define LED_POT 1
#define LED_LDR 2
#define BUTTON 2
#define SETPOINT_POT 512

static inline void initADC();
static inline void initPorts();
static inline void initINT0();
static inline void led_on(uint8_t pin);
static inline void led_off(uint8_t pin);
static inline void blink_twice();
static inline void switch_ADC_channel(uint8_t channel);
static inline uint16_t readADC();

volatile uint8_t mode=1;  //0=NORMAl, 1=NIGHT

typedef enum {
	STARTING,
	READ_POT,
	READ_LDR,
	CHECK_MODE
} state_t;

ISR(INT0_vect){
	mode ^=1;
}

int main(){
	state_t currentState=STARTING;
	
	initADC();
	initPorts();
	initINT0();
	sei();
	
	while(1){
		switch(currentState){
			case STARTING:
			blink_twice();
			_delay_ms(500);
			currentState=CHECK_MODE;
			break;
			case READ_LDR:
			switch_ADC_channel(1);
			if(readADC()<750){
				led_on(LED_LDR);
				}else{
				led_off(LED_LDR);
			}
			currentState=CHECK_MODE;
			break;
			case READ_POT:
			switch_ADC_channel(0);
			if(readADC()>SETPOINT_POT){
				led_on(LED_POT);
				}else{
				led_off(LED_POT);
			}
			currentState=CHECK_MODE;
			break;
			case CHECK_MODE:
			if(mode){
				currentState=READ_LDR;
				}else{
				currentState=READ_POT;
			}
			break;
		}
	}
}

static inline void zeroADC(){
	ADCSRA=0x00;
	ADMUX=0x00;
}

static inline void initADC(){
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

static inline void initINT0(){
	EICRA|=(1<<ISC01);// INT0-Falling edge
	EIMSK|=(1<<INT0);// Enable INT0;
}


static inline uint16_t readADC(){
	
	ADCSRA|=(1<<ADSC);
	while((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADC;
}


static inline void initPorts(){
	DDRB|=(1<<LED_START)|(1<<LED_POT)|(1<<LED_LDR);
	PORTD|=(1<<BUTTON);
}

static inline void led_on(uint8_t pin){
	PORTB|=(1<<pin);
}

static inline void led_off(uint8_t pin){
	PORTB&=~(1<<pin);
}

static inline void blink_twice(){
	int i;
	for (i=0; i<2; i++)
	{
		led_on(LED_START);
		_delay_ms(250);
		led_off(LED_START);
		_delay_ms(250);
	}
}

static inline void switch_ADC_channel(uint8_t channel){
	zeroADC();
	initADC();
	ADMUX|=(channel<<MUX0)|(1<<REFS0);
}


