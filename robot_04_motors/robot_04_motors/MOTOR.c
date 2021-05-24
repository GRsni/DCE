/*
 * MOTOR.c
 *
 * Created: 24/05/2021 11:53:35
 *  Author: DCE
 */ 

#include "MOTOR.h"
#include "TIMER.h"

void init_MOTOR()
{
	init_TIMER4A_PWM_Phase();
	init_TIMER4D_PWM_Phase();
	init_TIMER4_WFG_mode();
	init_TIMER4_freq_div();
}

void forward_MOTOR(uint8_t percent)
{
	uint8_t speed=calc_speed(percent);
	DDRC |= (1<<MOTOR_IZQ);
	DDRD |= (1<<MOTOR_DER);
	
	PORTD |= (1<<FORWARD_IZQ);
	PORTE |= (1<<FORWARD_DER);
	
	duty_TIMER4A_PWM_Phase(speed);
	duty_TIMER4D_PWM_Phase(speed);
	start_TIMER4_PWM_Phase();
}

void backwards_MOTOR(uint8_t percent)
{
	uint8_t speed=calc_speed(percent);
	DDRC |= (1<<MOTOR_IZQ);
	DDRD |= (1<<MOTOR_DER);
	
	PORTD &= (0<<FORWARD_IZQ);
	PORTE &= (0<<FORWARD_DER);
	
	duty_TIMER4A_PWM_Phase(speed);
	duty_TIMER4D_PWM_Phase(speed);
	start_TIMER4_PWM_Phase();
}
