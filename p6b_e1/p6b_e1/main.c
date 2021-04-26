/*
 * p6b_e1.c
 *
 * Created: 26/04/2021 12:24:40
 * Author : DCE
 */ 

#define  F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>

#include "TIMER.h"
#include "LED.h"

#define LED 2

void init_TIMER_CTC_ports();
void init_LED_ports();

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

void init_TIMER_CTC_ports()
{
	DDRB 	
}

