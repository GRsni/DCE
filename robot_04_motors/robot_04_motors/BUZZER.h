/*
* BUZZER.h
*
* Librería header-only para el control del 
* altavoz en el robot 2WD MiniQ
*
* Created: 13/05/2021 20:59:12
*  Author: Santiago Mas
*/

#include <avr/io.h>
#include <util/delay.h>


#ifndef BUZZER_H
#define BUZZER_H

//Definicion de puerto y pin del altavoz
#define BUZZER_PIN 2
#define BUZZER_PORT PORTB

//Definicion de constantes de periodo de sonidos
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
	init_TIMER0_CTC();
	init_TIMER1_CTC();
}

/*
* Funcion de generacion de tono empleando los temporizadores
* hardware del MCU ATmega32U4 (recomendada)
*
* @param	ms		Milisegundos de duracion del tono
* @param	note	Tono a reproducir
*
* @return	No devuelve nada
*/
static inline void BUZZER_timer_play_note(uint32_t ms, uint16_t note)
{
	init_TIMER0_CTC();
	init_TIMER1_CTC();
	uint8_t freq_value = (uint8_t)(note / 16);
	duty_TIMER0_Phase(freq_value);
	uint16_t timer_value = (uint16_t)(ms*1000/64);
	duty_TIMER1_Phase(timer_value);
	start_TIMER0_CTC();
	start_TIMER1_CTC();
}

/*
*
* Función de generacion de tono
*
* @param	ms			Milisegundos de duracion del tono
* @param	note		Tono a reproducir
*
* @result	No devuelve nada
*/
static inline void BUZZER_play_note(uint32_t ms, uint16_t note){
	uint32_t cycles=ms*1000/note;
	for(uint32_t i=0; i<cycles; i++){
		BUZZER_PORT ^= (1<<BUZZER_PIN);
		_delay_us(note);
	}
}


#endif //BUZZER_H
