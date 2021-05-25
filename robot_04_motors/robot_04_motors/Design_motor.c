/*
* main.c
*
* Created: 25/05/2021 14:37:06
*  Author: yasteer
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include "MOTOR.h"
#include "BUZZER.h"


typedef enum state_t{
	INIT,
	TEST,
	STOP
}STATES;

int main()
{
	STATES current_state= INIT;
	uint8_t beep_counter=0;

	BUZZER_init_port();
	MOTOR_init();
	
	
	MOTOR_start_sequence();
	while(1){

		switch(current_state)
		{
			case INIT:
			BUZZER_play_note(1, NOTE_SOL);
			current_state=TEST;
			break;
			case TEST:
			MOTOR_test();
			current_state=STOP;
			break;
			case STOP:
			_delay_ms(3000);
			for(beep_counter=0; beep_counter<3; beep_counter++){
				BUZZER_play_note(1, NOTE_DO_UP);
				_delay_ms(150);
			}
			current_state=INIT;
			break;
		}
	}
}