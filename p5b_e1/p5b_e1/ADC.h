#include <avr/io.h>
#include <stdbool.h>

#ifndef ADC_H
#define ADC_H

static inline void initADC_Polling(){
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

static inline void initADC_INT(){
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

static inline void zeroADC(){
	ADCSRA=0x00;
	ADMUX=0x00;
}

static inline void switch_ADC_channel(uint8_t channel, bool isPolling){
	zeroADC();
	if(isPolling){
		initADC_Polling();
		}else{
		initADC_INT();
	}
	ADMUX|=(channel<<MUX0)|(1<<REFS0);
}

static inline uint8_t readADC(){
	ADCSRA|=(1<<ADSC);
	while((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADC;
}

#endif