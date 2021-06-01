/*
* Design_motor.c
*
* Programa para el control del robot empleando 
* una maquina de estado
*
* Created: 25/05/2021 14:37:06
*  Author: Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include "MOTOR.h"
#include "BUZZER.h"

//Definicion de estados de la maquina de estados
//	INIT -> TEST -> STOP -
//   ^-------------------|
typedef enum state_t{
	INIT,
	TEST,
	STOP
}STATES;

int main()
{
	STATES current_state= INIT;
	uint8_t beep_counter=0;
	
	//------- Configuracion de puertos -----------
	BUZZER_init_port();
	MOTOR_init();
	
	//-------- Programa principal -----------------
	MOTOR_start_sequence();
	while(1){
		//---- Codigo de maquina de estado
		switch(current_state)
		{
			case INIT:
			BUZZER_play_note(1000, NOTE_SOL);
			current_state=TEST;
			break;
			case TEST:
			MOTOR_test();
			current_state=STOP;
			break;
			case STOP:
			_delay_ms(3000);
			for(beep_counter=0; beep_counter<3; beep_counter++){
				BUZZER_play_note(1000, NOTE_DO_UP);
				_delay_ms(150);
			}
			current_state=INIT;
			break;
		}
	}
}