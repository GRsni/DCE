/*
* TEST_complete_motor.c
*
* Programa de testeo de la funcionalidad
* completa de los motores del robot 2WD MiniQ
* 
* Created: 24/05/2021 10:30:25
* Author : Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "MOTOR.h"

int main(void)
{
	//------ Configuracion de puertos --------
	MOTOR_init();
	
	//--------- Programa principal -----------
	MOTOR_start_sequence();
	while (1)
	{
		MOTOR_forwards(50);
		_delay_ms(500);
		MOTOR_backwards(50);
		_delay_ms(500);
		MOTOR_stop();
		_delay_ms(1000);
		MOTOR_turn_left();
		MOTOR_stop();
		_delay_ms(1000);
		MOTOR_turn_right();
		MOTOR_stop();
		_delay_ms(1000);
		
	}
}

