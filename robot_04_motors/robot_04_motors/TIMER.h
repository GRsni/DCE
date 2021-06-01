/*
* TIMER.h
*
* Libreria para controlar los temporizadores hardware
* que posee el microcontrolador ATmega32U4.
*
* La interfaz diseñada permite configurar y usar los
* temporizadores 0, 1, y los puertos A y D del 4.
*
* Created: 24/05/2021 11:50:38
*  Author: Santiago Mas
*/

#include <avr/io.h>

#ifndef TIMER_H
#define TIMER_H


/*
* Funcion para inicializar los parametros del 
* TIMER hardware 0: CTC, prescaler y bandera
* de interrupcion
*
* @return	No devuelve nada
*/

static inline void init_TIMER0_CTC()
{
	TCCR0A |= (1<<COM0A0)|(1<<WGM01);		//Enable timer0 CTC Toggle on compare match
	TCCR0B |= (1<<CS02);					//Prescaler = 256 => 16us per cycle
	TIMSK0 |= (1<<OCIE0A);					//Enable compare match A interrupt handle
	TCNT0 = 0;
}

/*
* Funcion para deshabilitar toda la
* configuracion del TIMER0
*
*
* @return	No devuelve nada
*/
static inline void disable_TIMER0_CTC()
{
	TCCR0A &= (0<<COM0A0)|(1<<WGM01);
	TCCR0B &= (0<<CS02);
	TIMSK0 &= (0<<OCIE0A);
}


/*
* Funcion para establecer el ciclo de trabajo
* del TIMER0
* 
* @param	value	Valor del comparador
*
* @return	No devuelve nada
*/
static inline void duty_TIMER0_Phase(uint8_t value)
{
	OCR0A = value;			
}

/*
* Funcion para iniciar el TIMER0 estableciendo el 
* contador TCNT0 a 0
*
* @ return	No devuelve nada
*/
static inline void start_TIMER0_CTC()
{
	TCNT0 = 0;
	TIMSK0 |= (1<<OCIE0A);					//Enable compare match A interrupt handle
}

/*
* Funcion para inicialiazr los parametros del
* TIMER hardware 1: CTC, prescaler y bandera 
* de interrupcion
*
* @return	No devuelve nada
*/
static inline void init_TIMER1_CTC()
{
	TCCR1A |= (1<<COM1A0)|(1<<WGM12);	//Enable timer1 CTC Toggle on compare match
	TCCR1B |= (1<<CS12)|(1<<CS10);		//Prescaler = 1024 => 64us per cycle
	TIMSK1 |= (1<<OCIE1A);				//Enable compare match A interrupt handle
	TCNT1 = 0;
}

/*
* Funcion para deshabilitar toda la
* configuracion del TIMER1
*
*
* @return	No devuelve nada
*/
static inline void disable_TIMER1_CTC()
{
	TCCR1A &= (0<<COM1A0)|(1<<WGM12);
	TCCR1B &= (0<<CS12) && (0<<CS10);
	TIMSK1 &= (0<<OCIE1A);
}

/*
* Funcion para establecer el ciclo de trabajo
* del TIMER1
*
* @param	value	Valor del comparador
*
* @return	No devuelve nada
*/
static inline void duty_TIMER1_Phase(uint16_t value)
{
	OCR1A = value;
}

/*
* Funcion para iniciar el TIMER1 estableciendo el
* contador TCNT1 a 0
*
* @ return	No devuelve nada
*/
static inline void start_TIMER1_CTC()
{
	TCNT1 = 0;
	TIMSK1 |= (1<<OCIE1A);				//Enable compare match A interrupt handle
}


/*
* Funcion para inicializar el TIMER4A en modo
* PWM en fase correcta
*
* @return	No devuelve nada
*/
static inline void init_TIMER4A_PWM_Phase()
{
	TCCR4A|=(1<<PWM4A)|(1<<COM4A0);
}

/*
* Funcion para inicilizar el TIMER4D en modo
* PWM en fase correcta
*
* @return	No devuelve nada
*/
static inline void init_TIMER4D_PWM_Phase()
{
	TCCR4C |= (1<<PWM4D)|(1<<COM4D1);
}

/*
* Funcion para configurar el divisor de 
* frecuencia del TIMER4
*
* @return	No devuelve nada
*/
static inline void init_TIMER4_freq_div()
{
	TCCR4B |= (1<<CS42)|(1<<CS41)|(1<<CS40); //Prescaler = 64 
}

/*
* Funcion para configurar el modo de 
* generacion de onda del PWM
*
* @return	No devuelve nada
*/
static inline void init_TIMER4_WFG_mode()
{
	TCCR4D |= (1<<WGM40);
}


/*
* Funcion para iniciar el TIMER4 estableciendo el
* contador TCNT4 a 0
*
* @ return	No devuelve nada
*/
static inline void start_TIMER4_PWM_Phase()
{
	TCNT4=0;
}

/*
* Funcion para establecer el ciclo de trabajo del contador
* OCR0A (contador invertido)
*
* @param	valuuOCR0A	Valor del comparador
*
* @return	No devuelve nada
*/
static inline void duty_TIMER4A_PWM_Phase(uint8_t valueOCR0A)
{
	OCR4A = 255 - valueOCR0A;
}

/*
* Funcion para establecer el ciclo de trabajo del contador
* OCR0D 
*
* @param	valuuOCR0D	Valor del comparador
*
* @return	No devuelve nada
*/
static inline void duty_TIMER4D_PWM_Phase(uint8_t valueOCR4D)
{
	OCR4D = valueOCR4D;
}

#endif //TIMER_H