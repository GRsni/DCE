/*
* TIMER0.h
*
* Created: 26/04/2021 9:51:05
*  Author: DCE
*/

#ifndef TIMER_H
#define TIMER_H

void init_TIMER0_INT();

void init_TIMER0_polling();

void init_TIMER0_prescaler();

void set_TIMER0_value(uint8_t value);

void set_TIMER0_ms(uint16_t ms, uint8_t *ticks, uint8_t *remainder);

void init_TIMER1_INT();

void init_TIMER1_polling();

void init_TIMER1_prescaler();

void set_TIMER1_value(uint8_t value);

void set_TIMER1_ms(uint16_t ms, uint8_t *ticks, uint8_t *remainder);

#endif //TIMER_H