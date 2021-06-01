/*
* MOTOR.c
*
* Created: 24/05/2021 11:53:35
*  Author: DCE
*/

#include "MOTOR.h"

/*
* Funcion para inicializar la configuracion de
* los puertos asociados a los motores del robot
* Configura el TIMER4 en los puertos A y D, asi
* como los ENABLE como salida
*
* @return	No devuelve nada
*/
void MOTOR_init()
{
	init_TIMER4A_PWM_Phase();
	init_TIMER4D_PWM_Phase();
	init_TIMER4_WFG_mode();
	init_TIMER4_freq_div();
	
	DDRC |= (1<<MOTOR_LEFT);
	DDRD |= (1<<MOTOR_RIGHT);

}

/*
* Funcion para establecer el movimiento de las ruedas
* hacia delante a la velocidad indicada
*
* @param	speed	Porcentaje de velocidad de las ruedas
*
* @return	No devuelve nada
*/
void MOTOR_forwards(uint8_t percent)
{
	
	PORTD &= (0<<WHEEL_LEFT);
	PORTE &= (0<<WHEEL_RIGHT);
	
	MOTOR_set_wheel_speed(percent);

}

/*
* Funcion para establecer el movimiento de las ruedas
* hacia atras a la velocidad indicada
*
* @param	speed	Porcentaje de velocidad de las ruedas
*
* @return	No devuelve nada
*/
void MOTOR_backwards(uint8_t percent)
{

	PORTD |= (1<<WHEEL_LEFT);
	PORTE |= (1<<WHEEL_RIGHT);
	
	MOTOR_set_wheel_speed(percent);
}

/*
* Funcion para que el robot pivote a la
* izquierda 45 grados
*
* @return	No devuelve nada
*/
void MOTOR_turn_left()
{
	PORTD |= (1<<WHEEL_LEFT);
	PORTE &= (0<<WHEEL_RIGHT);
	MOTOR_set_wheel_speed(MOTOR_TURNING_SPEED);
}

/*
* Funcion para que el robot pivote a la
* derecha 45 grados
*
* @return	No devuelve nada
*/
void MOTOR_turn_right()
{
	PORTD &= (0<<WHEEL_LEFT);
	PORTE |= (1<<WHEEL_RIGHT);
	MOTOR_set_wheel_speed(MOTOR_TURNING_SPEED);
}

/*
* Rutina de pruebas de las funciones del motor
* El robot se mueve medio segundo hacia delante,
* se detiene un segundo, se mueve hacia atras
* medio segundo, se detiene un segundo, pivota
* a la izquierda, se detiene un segundo, pivota
* a la derecha y finalmente se detiene medio segundo
*
* @return	No devuelve nada
*/
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