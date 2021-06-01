#include "ADC.h"

/*
* Funcion para cambiar el canal que esta leyendo el
* conversor AD
*
* @param	channel	Canal nuevo a leer
* @param	mode	Modo de operacion, interrupcion o polling
*
* @return	No devuelve nada
*/
void switch_ADC_channel(uint8_t channel, uint8_t mode)
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

/*
* Funcion para leer un valor a traves del ADC
* configurado por polling
*
* @return	Devuelve el valor leido, entre 0 y 1024
*/
uint16_t read_ADC()
{
	ADCSRA|=(1<<ADSC);
	while((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADC;
}

/*
* Funcion que realiza 16 medidas del ADC seguidas, y calcula
* el valor medio, para minimizar variaciones del entorno
*
* @return	Devuelve el valor medio leido, entre 0 y 1024
*/
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
