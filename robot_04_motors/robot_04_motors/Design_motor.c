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

	BUZZER_init_port();
	MOTOR_init();
	MOTOR_stop();
	_delay_ms(1000);

	switch(current_state)
	{
		case INIT:
		break;
		case TEST:
		break;
		case STOP:
		break;
	}

}