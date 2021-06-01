/*
* siguelinea.c
*
* Programa para el control del robot 2WD MiniQ
*
* El robot es capaz de seguir una linea negra
* sobre un fondo blanco. En caso de salirse del
* recorrido, emite varios pitidos y retrocede
* intentando buscar el circuito.
*
* En caso de no encontrar el circuito de nuevo
* en 5 intentos, se detiene por completo y debe
* ser reiniciado.
*
* Created: 25/05/2021 19:51:21
*  Author: Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "MOTOR.h"
#include "BUZZER.h"
#include "OPTICAL.h"
#include "m_general.h"
#include "m_usb.h"


/*
* Rutina de inicio del programa. Inicia el
* motor y emite tres pitidos.
*
* @return	No devuelve nada
*/
static inline void inicio_programa();

/*
* Funcion de programa de siguelinea
*
*
* @return	No devuelve nada
*/
void follow_line();

/*
* Funcion para emitir 5 pitidos y esperar un
* tiempo determinado antes de volver a moverse
* Recibe el sonido a reproducir, la duracion de
* cada sonido, y el intervalo entre sonidos
*
* @param	note		Sonido a reproducir
* @param	beep_time	Duracion del sonido
* @param	beep_wait	Tiempo de espera entre sonidos
*
* @return	No devuelve nada
*/
void wait_and_beep(uint16_t note, uint16_t beep_time_ms, uint16_t beep_wait_ms);

/*
* Rutina de interrupcion del TIMER0, utilizada
* para la conmutacion del zumbador del robot
*
* @param	TIMER0_COMPA_vect	Registro de comparacion del TIMER0
*
* @return	No devuelve nada
*/
ISR(TIMER0_COMPA_vect)
{
	//Conmuta la señal de salida del altavoz
	BUZZER_PORT ^= (1<<BUZZER_PIN);
}

/*
* Rutina de interrupcion del TIMER1, utilizada
* para el control de la temporizacion del altavoz
*
* @param TIMER1_COMPA_vect	Registro de comparacion del TIMER1
*
* @return	No devuelve nada
*/
ISR(TIMER1_COMPA_vect)
{
	disable_TIMER0_CTC();
	disable_TIMER1_CTC();
}

//Contadores globales
uint16_t outside_counter = 0;
uint8_t stop_counter = 0;

int main(void)
{
	//--------- Configuracion de puertos ----------------
	MOTOR_init();
	BUZZER_init_port();
	OPTICAL_init();
	sei();
	
	//------------- Programa principal ------------------
	inicio_programa();
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

/*
* Rutina de inicio del programa. Inicia el
* motor y emite tres pitidos.
*
* @return	No devuelve nada
*/
static inline void inicio_programa()
{
	MOTOR_start_sequence();
	BUZZER_timer_play_note(500, NOTE_DO);
	_delay_ms(650);
	BUZZER_timer_play_note(500, NOTE_DO);
	_delay_ms(650);
	BUZZER_timer_play_note(1000, NOTE_DO_UP);
	_delay_ms(1100);
}

/*
* Funcion de programa de siguelinea
*
* Funcionamiento:
* Si los tres sensores centrales leen blanco,
* retrocede un poco y se detiene
* En otro caso, si los tres sensores leen negro,
* lee los sensores mas externos.
* Si los sensores de la izquierda o derecha leen negro
* rota el robot hacia ese lado, para centrarlo sobre
* la linea a seguir.
* En caso contrario, si el sensor central lee negro,
* se mueve hacia delante
*
* @return	No devuelve nada
*/
void follow_line()
{
	uint16_t sensor_left=OPTICAL_read_sensor(2);
	uint16_t sensor_center=OPTICAL_read_sensor(3);
	uint16_t sensor_right=OPTICAL_read_sensor(4);
	
	if(sensor_left> WHITE_THRESHOLD &&
		sensor_center > WHITE_THRESHOLD &&
		sensor_right> WHITE_THRESHOLD)//If all 3 front sensors read white, go backwards or stop
	{
		MOTOR_backwards(15);
		outside_counter++;
		
		if(outside_counter>100)
		{
			wait_and_beep(NOTE_DO_UP, 500, 600);
			
			outside_counter=0;
			stop_counter++;
		}
	}else
	{
		outside_counter=0;
		if(sensor_left < BLACK_THRESHOLD && 
			sensor_center && BLACK_THRESHOLD &&
			sensor_right <BLACK_THRESHOLD) //If all 3 main sensors read black, use outer sensors
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
				MOTOR_forwards(MOTOR_STRAIGHT_SPEED_MEDIUM);
			}
		}
	}
}

/*
* Funcion para emitir 5 pitidos y esperar un
* tiempo determinado antes de volver a moverse
* Recibe el sonido a reproducir, la duracion de 
* cada sonido, y el intervalo entre sonidos
*
* @param	note		Sonido a reproducir
* @param	beep_time	Duracion del sonido
* @param	beep_wait	Tiempo de espera entre sonidos
*
* @return	No devuelve nada
*/
void wait_and_beep(uint16_t note, uint16_t beep_time_ms, uint16_t beep_wait_ms)
{
	MOTOR_stop();
	for(int i=0; i<5; i++)
	{
		BUZZER_timer_play_note(beep_time_ms, note);
		_delay_ms(beep_wait_ms);
	}
	_delay_ms(4000);
}