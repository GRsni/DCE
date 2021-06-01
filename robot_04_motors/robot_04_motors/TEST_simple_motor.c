/*
 * TEST_simple_motor.c
 *
 * Programa inicial de pruebas para el control
 * de los motores DC del robot 2WD MiniQ
 *
 * Created: 25/05/2021 19:29:59
 *  Author: Santiago Mas
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "MOTOR.h"

int main(void)
{
	//-------- Configuracion de puertos -----------
	MOTOR_init();
	
	//---------- Programa principal ---------------
	MOTOR_start_sequence();
	while (1)
	{
		MOTOR_forwards(100);
		_delay_ms(1000);
		MOTOR_forwards(20);
		_delay_ms(1000);
	}
}