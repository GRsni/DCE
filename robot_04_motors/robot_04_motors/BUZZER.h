/*
* BUZZER.h
*
* Librería header-only para el control del altavoz en el robot 2WD MiniQ
*
* Created: 13/05/2021 20:59:12
*  Author: Santiago Mas
*/

#include <avr/io.h>
#include <util/delay.h>


#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_PIN 2
#define BUZZER_PORT PORTB

#define NOTE_DO 1915
#define NOTE_RE 1706
#define NOTE_MI	1519
#define NOTE_FA	1432
#define NOTE_SOL 1275
#define NOTE_LA	1136
#define NOTE_SI 1014
#define NOTE_DO_UP 957

/*
* Función de configuracion de puerto de altavoz como salida
*
* 
* @result No devuelve nada
*/
static inline void BUZZER_init_port()
{
	DDRB |= (1<<BUZZER_PIN);
}

/*
*
* Función de generacion de tono
*
* @param	seconds		Numero de segundos a reproducir el tono
* @param	note		Tono a reproducir
*	
* @result No devuelve nada
*/
static inline void BUZZER_play_note(uint32_t ms, uint16_t note){
	uint32_t cycles=ms*1000/note;
	for(uint32_t i=0; i<cycles; i++){
		BUZZER_PORT ^= (1<<BUZZER_PIN);
		_delay_us(note);
	}
}


#endif //BUZZER_H
