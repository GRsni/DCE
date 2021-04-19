#include "USART.h"

void USART_Init(uint16_t ubrr)
{
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

void USART_TX_char(unsigned char data)
{
	// (Polling) Wait for empty transmit buffer
	while(!(UCSR0A&(1<<UDRE0)));
	// Put data into buffer, sends the data
	UDR0=data;
}

void USART_TX_str(char * data, bool line_carry)
{
	while(*data){
		USART_TX_char(*data);
		data++;
	}
	if(line_carry){
		USART_TX_char('\r');
		USART_TX_char('\n');
	}
}

void USART_TX_str_padding(char *str, uint8_t max_size, bool line_carry)
{
	uint16_t str_size=strlen(str);
	uint16_t i=max_size-str_size;
	for(; i>0; i--){
		USART_TX_char(' ');
	}	
	USART_TX_str(str, line_carry);
}

unsigned char USART_RX_char(){
	// (Polling) Wait for empty transmit buffer
	while(!(UCSR0A&(1<<RXC0)));
	// Put data into buffer, sends the data
	unsigned char data=UDR0;
	UDR0=0;
	return data;
}