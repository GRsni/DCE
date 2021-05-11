#include <avr/io.h>
#include <stdbool.h>

#ifndef ADC_H
#define ADC_H

#define ADC_POLLING 1
#define ADC_INTERRUPT 0

void init_ADC_Polling();

void init_ADC_INT();

void zero_ADC();

void switch_ADC_channel(uint8_t channel, bool isPolling);

uint16_t read_ADC_polling();

uint16_t read_ADC_average();

uint16_t read_ADC_int();

#endif