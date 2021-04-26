/*
 * TIMER0.h
 *
 * Created: 26/04/2021 9:51:05
 *  Author: DCE
 */ 

#ifndef TIMER0_H
#define TIMER0_H

void init_TIMER0_INT();

void init_TIMER0_polling();

void init_TIMER0_prescaler();

void set_TIMER0_value(uint8_t value);

#endif //TIMER0_H