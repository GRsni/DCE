#include <avr/io.h>

#ifndef LED_H
#define LED_H

void led_on(uint8_t pin);

void led_off(uint8_t pin);

void led_blink(uint8_t pin);

#endif