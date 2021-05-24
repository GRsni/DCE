/*
* robot_04_motors.c
*
* Created: 24/05/2021 10:30:25
* Author : DCE
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "MOTOR.h"

int main(void)
{
	init_MOTOR();
	
	stop_MOTOR();
	while (1)
	{
		_delay_ms(1000);
		backwards_MOTOR(50);
		_delay_ms(1000);
		backwards_MOTOR(100);
	}
}

