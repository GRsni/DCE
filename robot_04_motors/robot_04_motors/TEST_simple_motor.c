/*
 * TEST_simple_motor.c
 *
 * Created: 25/05/2021 19:29:59
 *  Author: yasteer
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "MOTOR.h"

int main(void)
{
	MOTOR_init();
	
	
	MOTOR_stop();
	_delay_ms(1000);
	MOTOR_start();
	while (1)
	{
		MOTOR_forwards(100);
		_delay_ms(1000);
		MOTOR_forwards(20);
		_delay_ms(1000);
	}
}