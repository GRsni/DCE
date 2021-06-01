/*
* MOTOR.h
*
* Libreria para el control de los motores DC
* del robot 2WD MiniQ
*
* Created: 24/05/2021 11:50:15
*  Author: Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "TIMER.h"

#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_LEFT DDC6		//Constante del puerto asociado al PWM1
#define MOTOR_RIGHT DDD7	//Constante del puerto asociado al PWM2

#define WHEEL_LEFT PORTD6	//Constante del puerto asociado al EN1
#define WHEEL_RIGHT PORTE6	//Constante del puerto asociado al EN2

//Constantes para establecer velocidad de los motores
#define MOTOR_TURNING_SPEED 20	
#define MOTOR_STRAIGHT_SPEED_SLOW 20
#define MOTOR_STRAIGHT_SPEED_MEDIUM 50
#define MOTOR_STRAIGHT_SPEED_FAST 70


/*
* Funcion para inicializar la configuracion de 
* los puertos asociados a los motores del robot
* Configura el TIMER4 en los puertos A y D, asi 
* como los puertos ENABLE 
* 
* @return	No devuelve nada
*/
void MOTOR_init();

/*
* Funcion para detener el movimiento de las ruedas
*
* @return	No devuelve nada
*/
static inline void MOTOR_stop()
{
	duty_TIMER4A_PWM_Phase(0);
	duty_TIMER4D_PWM_Phase(0);
}

/*
* Funcion para inicializar el movimiento de las ruedas
* Configura los puertos del PWM, y los timers asociados
*
* @return	No devuelve nada
*/
static inline void MOTOR_start()
{
	DDRD |= (1<<WHEEL_LEFT);
	DDRE |= (1<<WHEEL_RIGHT);
	
	start_TIMER4_PWM_Phase();
}

/*
* Funcion para la rutina de inicio del motor
* Detiene el motor durante un segundo, y lo 
* habilita despues
*
* @return	No devuelve nada
*/
static inline void MOTOR_start_sequence()
{
	MOTOR_stop();
	_delay_ms(1000);
	MOTOR_start();
}

/*
* Funcion para calcular el valor del TIMER4
* en funcion del parametro de velocidad en 
* en porcentaje
*
* @param	percent		Velocidad de la rueda en porcentaje
*
* @return	Devuelve el valor de comparacion del TIMER4
*/
static inline uint8_t calc_speed(uint8_t percent)
{
	return 254 * percent / 100;
}

/*
* Funcion para configurar la velocidad de las ruedas
*
* @param	percentage	Porcentaje de velocidad de las ruedas
*
* @return	No devuelve nada
*/
static inline void MOTOR_set_wheel_speed(uint8_t percentage)
{
	uint8_t speed=calc_speed(percentage);
	duty_TIMER4A_PWM_Phase(speed);
	duty_TIMER4D_PWM_Phase(speed);
}

/*
* Funcion para establecer el movimiento de las ruedas
* hacia delante a la velocidad indicada
*
* @param	speed	Porcentaje de velocidad de las ruedas
*
* @return	No devuelve nada
*/
void MOTOR_forwards(uint8_t speed);

/*
* Funcion para establecer el movimiento de las ruedas
* hacia atras a la velocidad indicada
*
* @param	speed	Porcentaje de velocidad de las ruedas
*
* @return	No devuelve nada
*/
void MOTOR_backwards(uint8_t speed);

/*
* Funcion para que el robot pivote a la 
* izquierda 45 grados
*
* @return	No devuelve nada
*/
void MOTOR_turn_left();

/*
* Funcion para que el robot pivote a la
* derecha 45 grados
*
* @return	No devuelve nada
*/
void MOTOR_turn_right();

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
void MOTOR_test();

#endif //MOTOR_H