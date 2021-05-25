/*
* MOTOR.h
*
* Created: 24/05/2021 11:50:15
*  Author: DCE
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "TIMER.h"

#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_LEFT DDC6
#define MOTOR_RIGHT DDD7

#define WHEEL_LEFT PORTD6
#define WHEEL_RIGHT PORTE6

#define MOTOR_TURNING_SPEED 20

void MOTOR_init();

static inline void MOTOR_stop()
{
	duty_TIMER4A_PWM_Phase(0);
	duty_TIMER4D_PWM_Phase(0);
}

static inline void MOTOR_start()
{
	DDRD |= (1<<WHEEL_LEFT);
	DDRE |= (1<<WHEEL_RIGHT);
	
	start_TIMER4_PWM_Phase();
}


static inline void MOTOR_start_sequence()
{
	MOTOR_stop();
	_delay_ms(1000);
	MOTOR_start();
}

static inline uint8_t calc_speed(uint8_t percent)
{
	return 254 * percent / 100;
}

static inline void MOTOR_set_wheel_speed(uint8_t percentage)
{
	uint8_t speed=calc_speed(percentage);
	duty_TIMER4A_PWM_Phase(speed);
	duty_TIMER4D_PWM_Phase(speed);
}

void MOTOR_forwards(uint8_t speed);

void MOTOR_backwards(uint8_t speed);

void MOTOR_turn_left();

void MOTOR_turn_right();

void MOTOR_test();

#endif //MOTOR_H