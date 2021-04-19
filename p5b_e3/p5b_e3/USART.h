#include <avr/io.h>
#include <stdbool.h>
#include <string.h>

#ifndef USART_H
#define USART_H

void USART_Init(uint16_t ubrr);

void USART_TX_char(unsigned char data);

void USART_TX_str(char* str, bool line_carry);

void USART_TX_str_padding(char *str, uint8_t size, bool line_carry);

unsigned char USART_RX_char();

#endif