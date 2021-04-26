
#include "LED.h"


void led_on( uint8_t pin)
{
	PORTB |= (1<<pin);
}

void led_off( uint8_t pin)
{
	PORTB &= ~(1<<pin);
}

void led_blink(uint8_t pin)
{
	PORTB ^= (1<<pin);
}