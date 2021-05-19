/*
* robot_03_optical.c
*
* Codigo C para uso del sensor infrarrojo
* IR0 del robot 2WD MinQ
*
* Created: 17/05/2021 9:45:22
* Author : Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "ADC.h"
#include "BUZZER.h"

#define WHITE_THRESHOLD 900
#define BLACK_THRESHOLD 400

#define IR0_CHANNEL 7


static inline void play_note_from_value(uint8_t seconds, uint16_t value);

int main(void)
{
	uint16_t value;
	
	//--------------- CONFIGURACION DE PUERTOS ----------------
	BUZZER_init_port();
	init_ADC_Polling();
	switch_ADC_channel(IR0_CHANNEL, ADC_IS_POLLING); //Se cambia el ADC al canal correspondiente
	
	//----------------- PROGRAMA PRINCIPAL -------------------
	
	while (1)
	{
		value=read_ADC_average();		// Se lee el valor del IR a traves del ADC	
		play_note_from_value(1, value);
		
	}
}

/*
* Funcion para producir un sonido dependiendo del valor leido
* por el ADC. Permite seleccionar el tiempo de reproduccion
*
* @param	seconds	Tiempo a reproducir el sonido
* @param	value	Valor producido por el ADC
*
* @return	No devuelve nada
*/
static inline void play_note_from_value(uint8_t seconds, uint16_t value){
	if(value>WHITE_THRESHOLD)
	{
		BUZZER_play_note(seconds, NOTE_DO_UP);
	}
	else if (value < BLACK_THRESHOLD)
	{
		BUZZER_play_note(seconds,NOTE_DO);
	}
	else
	{
		BUZZER_play_note(seconds, NOTE_SOL);
	}
}

