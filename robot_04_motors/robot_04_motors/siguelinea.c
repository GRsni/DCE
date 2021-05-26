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

#define MOTOR_SPEED 30

void follow_line();

uint16_t outside_counter=0;

int main(void)
{
	MOTOR_init();
	BUZZER_init_port();
	OPTICAL_init();
	
	
	MOTOR_start_sequence();
	BUZZER_play_note(500, NOTE_DO);
	_delay_ms(150);
	BUZZER_play_note(500, NOTE_DO);
	_delay_ms(150);
	while (1)
	{
		follow_line();
	}
}

void follow_line()
{
	uint16_t sensor_left=OPTICAL_read_sensor(2);
	uint16_t sensor_center=OPTICAL_read_sensor(3);
	uint16_t sensor_right=OPTICAL_read_sensor(4);
	
	
	if(sensor_left < BLACK_THRESHOLD && sensor_center && BLACK_THRESHOLD && sensor_right <BLACK_THRESHOLD) //If all 3 main sensors read black, use most external sensors
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
		else if(sensor_left> WHITE_THRESHOLD && sensor_center > WHITE_THRESHOLD && sensor_right> WHITE_THRESHOLD)//In any other case, beep and stop
		{
			MOTOR_backwards(10);
			outside_counter++;
			
			if(outside_counter>1000)
			{
				MOTOR_stop();
				for(int i=0; i<3; i++)
				{
				BUZZER_play_note(500, NOTE_DO_UP);
				_delay_ms(100);
				}
				_delay_ms(5000);
				outside_counter=0;
			}
			
		}
	}
}