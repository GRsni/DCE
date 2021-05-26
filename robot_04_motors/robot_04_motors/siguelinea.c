/*
* siguelinea.c
*
* Created: 25/05/2021 19:51:21
*  Author: yasteer
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "MOTOR.h"
#include "BUZZER.h"
#include "OPTICAL.h"
#include "m_general.h"
#include "m_usb.h"

#define MOTOR_SPEED 30

void follow_line();

ISR(TIMER0_COMPA_vect)
{
	BUZZER_PORT ^= (1<<BUZZER_PIN);
}

ISR(TIMER1_COMPA_vect)
{
	TIMSK0 &= (0<<OCIE0A);
	TIMSK1 &= (0<<OCIE1A);
}

uint16_t outside_counter = 0;
uint8_t stop_counter = 0;

int main(void)
{
	MOTOR_init();
	BUZZER_init_port();
	OPTICAL_init();
	sei();
	
	
	MOTOR_start_sequence();
	BUZZER_timer_play_note(500, NOTE_DO);
	_delay_ms(650);
	BUZZER_timer_play_note(500, NOTE_DO);
	_delay_ms(650);
	BUZZER_timer_play_note(1000, NOTE_DO_UP);
	_delay_ms(1100);
	while (1)
	{
		if(stop_counter<3)
		{
			follow_line();
		}
		else
		{
			BUZZER_timer_play_note(500, NOTE_DO_UP);
			_delay_ms(800);
		}
	}
}

void follow_line()
{
	uint16_t sensor_left=OPTICAL_read_sensor(2);
	uint16_t sensor_center=OPTICAL_read_sensor(3);
	uint16_t sensor_right=OPTICAL_read_sensor(4);
	
	if(sensor_left> WHITE_THRESHOLD && sensor_center > WHITE_THRESHOLD && sensor_right> WHITE_THRESHOLD)//If all 3 front sensors read white, go backwards or stop
	{
		MOTOR_backwards(15);
		outside_counter++;
		
		if(outside_counter>100)
		{
			MOTOR_stop();
			for(int i=0; i<5; i++)
			{
				BUZZER_timer_play_note(500, NOTE_DO_UP);
				_delay_ms(600);
			}
			_delay_ms(5000);
			
			outside_counter=0;
			stop_counter++;
		}
	}else
	{
		outside_counter=0;
		if(sensor_left < BLACK_THRESHOLD && sensor_center && BLACK_THRESHOLD && sensor_right <BLACK_THRESHOLD) //If all 3 main sensors read black, use outer sensors
		{
			
			uint16_t sensor_most_left=OPTICAL_read_sensor(1);
			uint16_t sensor_most_right=OPTICAL_read_sensor(5);
			if(sensor_most_left <BLACK_THRESHOLD)
			{
				MOTOR_turn_left();
			}else if(sensor_most_right < BLACK_THRESHOLD)
			{
				MOTOR_turn_right();
			}
		}else
		{
			if(sensor_left<BLACK_THRESHOLD) //If the left sensor sees black, turn right
			{
				MOTOR_turn_left();
			}else if(sensor_right<BLACK_THRESHOLD) //Else if the right sensor sees black, turn left
			{
				MOTOR_turn_right();
			}else if(sensor_center < BLACK_THRESHOLD)	//In case the center sensor sees black, continue forwards
			{
				MOTOR_forwards(MOTOR_SPEED);
			}
		}
	}
}