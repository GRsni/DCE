/*
 * OPTICAL.h
 *
 * Created: 25/05/2021 19:54:51
 *  Author: yasteer
 */ 

#include "m_general.h"
#include "m_usb.h"

#include "ADC.h"

#ifndef OPTICAL_H
#define OPTICAL_H

#define WHITE_THRESHOLD 900
#define BLACK_THRESHOLD 800

#define IR0_CHANNEL 7
#define IR1_CHANNEL 6
#define IR2_CHANNEL 5
#define IR3_CHANNEL 4
#define IR4_CHANNEL 1

static inline void OPTICAL_init()
{
	init_ADC_Polling();
}

/*
* Funcion para transformar de un caracter de '1' a '5', a
* un canal del lector IR de 7 a 3
*
* @param	option	Opcion introducida por usuario
*
* @return	Devuelve un entero entre {7, 6, 5, 4, 1}
*/
static inline uint8_t option_to_IR_channel(uint8_t option){
	switch(option){
		case 1:
		return IR0_CHANNEL;
		case 2:
		return IR1_CHANNEL;
		case 3:
		return IR2_CHANNEL;
		case 4:
		return IR3_CHANNEL;
		case 5:
		return IR4_CHANNEL;
		default:
		return IR0_CHANNEL;
	}
}

static inline uint16_t OPTICAL_read_sensor(uint8_t sensor)
{
	switch_ADC_channel(option_to_IR_channel(sensor), ADC_IS_POLLING);
	return read_ADC_average();
}




#endif
