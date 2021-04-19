#include <avr/io.h>

#include "USART.h"

static inline void USART_Init(uint16_t ubrr){
	//1.-Set baud rate
	UBRR0H =(unsigned char)(ubrr>>8);
	UBRR0L =(unsigned char) ubrr;
	//2.-Set the speed: Normal Asynchronous
	UCSR0A &= (0<<U2X0);// NOT default option!!!!!
	//3.-Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	//4.-Set frame format: 8data, 1stop bit
	UCSR0C |= (3<<UCSZ00);
}

static inline void USART_TX_char(unsigned char data){
	// (Polling) Wait for empty transmit buffer
	while(!(UCSR0A&(1<<UDRE0)));
	// Put data into buffer, sends the data
	UDR0=data;
}