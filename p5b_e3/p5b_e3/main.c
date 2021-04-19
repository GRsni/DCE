/*
* p5b_e3.c
*
* Created: 19/04/2021 11:14:21
* Author : DCE
*/

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ADC.h"
#include "USART.h"
#include "LED.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 //103 cycles system-clk

#define LED_LDR 0
#define LED_POT 1
#define POT_CHANNEL 0
#define LDR_CHANNEL 1
#define ADC_POLLING 1

static inline void init_ports();
static inline bool correct_option(unsigned char option);

char *menu_str=	"\e[u\e[s+--------------------------------------------------+\r\n"
						"| MENU P5B E3: Elige la opcion a leer              |\r\n"
						"| A: Leer dato del LDR                             |\r\n"
						"| B: Leer dato del potenciometro                   |\r\n"
						"+--------------------------------------------------+\r\n"
						" Opcion: ";

char *result_str="\r\n Resultado: ";

int main(void)
{
	USART_Init(MYUBRR);
	init_ports();
	switch_ADC_channel(POT_CHANNEL, ADC_POLLING);

	while (1)
	{
		USART_TX_str(menu_str, false);
		unsigned char option='0';
		//do{
			option='0';
			option=USART_RX_char();
		//}while(!correct_option(option));
		
		USART_TX_char(option);
		switch(option){
			case 'a':
			case 'A':
			switch_ADC_channel(LDR_CHANNEL, ADC_POLLING);
			break;
			case 'b':
			case 'B':
			switch_ADC_channel(POT_CHANNEL, ADC_POLLING);
			break;
		}
		
		USART_TX_str(result_str, false);
		
		uint16_t value=read_ADC_average();
		if(value>512){
			led_on(LED_POT);
			}else{
			led_off(LED_POT);
		}
		char value_str[5]={0};
		utoa(value, value_str, 10);
		
		USART_TX_str_padding(value_str, 5, false);
		//_delay_ms(1000);
		
	}
}

static inline void init_ports(){
	DDRB|=(1<<LED_POT)|(1<<LED_LDR);
}

static inline bool correct_option(unsigned char option){
	return option== 'A' || option=='a' || option== 'B' || option=='b';
}

