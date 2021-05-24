/*
* ADC.h
*
* Librería para el control del periferico ADC 
* en el robot 2WD MiniQ
*
* Created: 13/05/2021 20:59:12
*  Author: Santiago Mas
*/

#include <avr/io.h>

#ifndef ADC_H
#define ADC_H

#define ADC_IS_POLLING 1	//Constante para seleccionar ADC por polling
#define ADC_IS_INTERRUPT 0	//Constante para seleccionar ADC por interrupciones

/*
* Función para inicializar el conversor AD en modo polling
* 
* @return	No devuelve nada
*/
static inline void init_ADC_Polling()
{
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

/*
* Función para inicializar el conversor AD en modo interrupcion
*
* @return	No devuelve nada
*/
static inline void init_ADC_INT()
{
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

/*
* Funcion para limpiar los puertos dedicados al conversor AD
* previo a asignar nuevos modos de operacion o canales
*
* @return	No devuelve nada
*/
static inline void zero_ADC()
{
	ADCSRA=0x00;
	ADMUX=0x00;
}


/*
* Funcion para cambiar el canal que esta leyendo el
* conversor AD
*
* @param	channel	Canal nuevo a leer
* @param	mode	Modo de operacion, interrupcion o polling
*
* @return	No devuelve nada
*/
void switch_ADC_channel(uint8_t channel, uint8_t mode);

/*
* Funcion para leer un valor a traves del ADC 
* configurado por polling
*
* @return	Devuelve el valor leido, entre 0 y 1024
*/
uint16_t read_ADC();

/*
* Funcion que realiza 16 medidas del ADC seguidas, y calcula 
* el valor medio, para minimizar variaciones del entorno
*
* @return	Devuelve el valor medio leido, entre 0 y 1024
*/
uint16_t read_ADC_average();

#endif