/*
* MOTOR.c
*
* Created: 24/05/2021 11:53:35
*  Author: DCE
*/

#include "MOTOR.h"

void MOTOR_init()
{
	init_TIMER4A_PWM_Phase();
	init_TIMER4D_PWM_Phase();
	init_TIMER4_WFG_mode();
	init_TIMER4_freq_div();
	
	DDRC |= (1<<MOTOR_LEFT);
	DDRD |= (1<<MOTOR_RIGHT);

}

void MOTOR_backwards(uint8_t percent)
{

	PORTD |= (1<<WHEEL_LEFT);
	PORTE |= (1<<WHEEL_RIGHT);
	
	MOTOR_set_wheel_speed(percent);
}

void MOTOR_forwards(uint8_t percent)
{
	
	PORTD &= (0<<WHEEL_LEFT);
	PORTE &= (0<<WHEEL_RIGHT);
	
	MOTOR_set_wheel_speed(percent);

}

void MOTOR_turn_left()
{
	PORTD |= (1<<WHEEL_LEFT);
	PORTE &= (0<<WHEEL_RIGHT);
	MOTOR_set_wheel_speed(MOTOR_TURNING_SPEED);
}

void MOTOR_turn_right()
{
	PORTD &= (0<<WHEEL_LEFT);
	PORTE |= (1<<WHEEL_RIGHT);
	MOTOR_set_wheel_speed(MOTOR_TURNING_SPEED);
}

void MOTOR_test()
{
	MOTOR_forwards(50);
	_delay_ms(500);
	MOTOR_stop();
	_delay_ms(1000);
	MOTOR_backwards(50);
	_delay_ms(500);
	MOTOR_stop();
	_delay_ms(1000);
	MOTOR_turn_left();
	MOTOR_stop();
	_delay_ms(1000);
	MOTOR_turn_right();
	MOTOR_stop();
	_delay_ms(500);
}