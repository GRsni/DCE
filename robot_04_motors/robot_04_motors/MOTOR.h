/*
 * MOTOR.h
 *
 * Created: 24/05/2021 11:50:15
 *  Author: DCE
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_IZQ PORTC6
#define MOTOR_DER PORTD7

#define FORWARD_IZQ PORTD6
#define FORWARD_DER PORTE6

void init_MOTOR();

static inline void stop_MOTOR()
{
	DDRC &= (0<<MOTOR_IZQ);
	DDRD &= (0<<MOTOR_DER);
	_delay_ms(1500);
}

static inline uint8_t calc_speed(uint8_t percent)
{
	return 254 * percent / 100;
}

void forward_MOTOR(uint8_t speed);

void backwards_MOTOR(uint8_t speed);


#endif //MOTOR_H