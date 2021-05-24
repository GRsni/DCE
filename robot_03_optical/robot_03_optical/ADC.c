#include "ADC.h"


void switch_ADC_channel(uint8_t channel, bool mode)
{
	zero_ADC();
	if(mode)
	{
		init_ADC_Polling();
	}
	else
	{
		init_ADC_INT();
	}
	ADMUX|=(channel<<MUX0)|(1<<REFS0);
}

uint16_t read_ADC()
{
	ADCSRA|=(1<<ADSC);
	while((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADC;
}

uint16_t read_ADC_average(){
	uint16_t acum=0;
	int i;
	
	read_ADC();			//Read the first value and discard it
						//to avoid timing issues
	for(i=16; i>0; i--)
	{
		acum+=read_ADC();
	}
	return (acum>>4);
}
