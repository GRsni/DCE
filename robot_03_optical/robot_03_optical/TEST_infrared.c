/*
* TEST_infrarred.c
*
* Codigo de testeo de los sensores infrarrojos
* del robot 2WD MiniQ con conexión serie a traves
* de puerto USB
*
* Created: 17/05/2021 9:45:22
* Author : Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>

#include "m_general.h"
#include "m_usb.h"
#include "ADC.h"
#include "BUZZER.h"

#define WHITE_THRESHOLD 900
#define BLACK_THRESHOLD 400


static inline void print_menu();
static inline unsigned char recieve_valid_option();
static inline bool check_option(unsigned char option);
static inline uint8_t option_to_IR_channel(unsigned char option);
static inline void play_note_from_value(uint8_t seconds, uint16_t value);

int main(void)
{
	uint16_t value;
	
	//--------------- CONFIGURACION DE PUERTOS ----------------
	BUZZER_init_port();
	init_ADC_Polling();
	m_usb_init();
	while(!m_usb_isconnected());
	
	
	//----------------- PROGRAMA PRINCIPAL -------------------
	m_usb_tx_string("Hello world");
	
	while (1)
	{
		print_menu();  // Se imprime el menu principal

		unsigned char option=recieve_valid_option();	//Se lee por consola el lector a usar
		
		uint8_t channel=option_to_IR_channel(option); //Se transforma el caracter en el canal del IR
		m_usb_tx_string("Leyendo IR ");
		m_usb_tx_int(channel);
		m_usb_tx_string("\n\r");
		
		switch_ADC_channel(channel, ADC_IS_POLLING); //Se cambia el ADC al canal correspondiente
		value=read_ADC_average();		// Se lee el valor del IR a traves del ADC
		
		m_usb_tx_string("\r\n Resultado: "); //Se muestra el valor leido por pantalla
		m_usb_tx_uint(value);
		m_usb_tx_string("     \n\r");
		play_note_from_value(1, value);
		
	}
}

/*
* Funcion para imprimir el menu del programa por consola. Envía
* la cadena por USB
*
* @return	No devuelve nada
*/
static inline void print_menu(){
	m_usb_tx_string("\e[u\e[s+--------------------------------------------------+\n\r"
	"| MENU TEST ROBOT : Elige el sensor a leer         |\n\r"
	"| 1: Leer sensor IR0                               |\n\r"
	"| 2: Leer sensor IR1                               |\n\r"
	"| 3: Leer sensor IR2                               |\n\r"
	"| 4: Leer sensor IR3                               |\n\r"
	"| 5: Leer sensor IR4                               |\n\r"
	"+--------------------------------------------------+\n\r"
	" Opcion: ");
}


/*
* Función que controla la recepción de la opcion introducida
* por teclado, y comprueba si es valido
*
* @return	Devuelve el caracter introducido por teclado
*/
static inline unsigned char recieve_valid_option(){
	unsigned char option='0';
	bool option_is_valid=true;
	do
	{
		if(m_usb_rx_available())
		{
			option = m_usb_rx_char();
		}
		option_is_valid=check_option(option);
	}while(!option_is_valid);
	return option;
}

/*
* Funcion para comprobar que la opcion introducida esta
* dentro del conjunto de opciones validas ('1' a '5')
*
* @param	option	Caracter introducido por teclado
*
* @return	Devuelve true si el caracter está en el conjunto valido
*/
static inline bool check_option(unsigned char option){
	return option>='1' && option<='5';
}

/*
* Funcion para transformar de un caracter de '1' a '5', a
* un canal del lector IR de 7 a 3
*
* @param	option	Opcion introducida por usuario
*
* @return	Devuelve un entero entre {7, 6, 5, 4, 1}
*/
static inline uint8_t option_to_IR_channel(unsigned char option){
	switch(option){
		case '1':
		return 7;
		case '2':
		return 6;
		case '3':
		return 5;
		case '4':
		return 4;
		case '5':
		return 1;
		default:
		return 7;
	}
}


/*
* Funcion para producir un sonido dependiendo del valor leido
* por el ADC. Permite seleccionar el tiempo de reproduccion
*
* @param	seconds	Tiempo a reproducir el sonido
* @param	value	Valor producido por el ADC
*
* @return	No devuelve nada
*/
static inline void play_note_from_value(uint8_t seconds, uint16_t value){
	if(value>WHITE_THRESHOLD)
	{
		BUZZER_play_note(seconds, NOTE_DO_UP);
	}
	else if (value < BLACK_THRESHOLD)
	{
		BUZZER_play_note(seconds,NOTE_DO);
	}
	else
	{
		BUZZER_play_note(seconds, NOTE_SOL);
	}
}

