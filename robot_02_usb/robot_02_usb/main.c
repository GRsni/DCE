/*
 * robot_02_usb.c
 *
 * Created: 17/05/2021 9:08:03
 * Author : DCE
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include "m_general.h"
#include "m_usb.h"


int main(void)
{
	unsigned int value;
	
	m_usb_init();
	while(!m_usb_isconnected());
	m_usb_tx_string("Hello world\n\r");
	
	while (1) 
    {
		if(m_usb_rx_available()){
			value=m_usb_rx_char();
			m_usb_tx_char(value);// Print the ASCII character
			m_usb_tx_char('\t');
			m_usb_tx_uint(value);// Print the decimal equivalent
			m_usb_tx_char('\n');
			m_usb_tx_char('\r');
			
		}
	}
}

