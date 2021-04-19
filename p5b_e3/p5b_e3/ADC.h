#include <avr/io.h>
#include <stdbool.h>

#ifndef ADC_H
#define ADC_H

void init_ADC_Polling();

void init_ADC_INT();

void zero_ADC();

void switch_ADC_channel(uint8_t channel, bool isPolling);

uint16_t read_ADC();

uint16_t read_ADC_average();

#endif