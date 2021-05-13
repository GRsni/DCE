/*
* robot_01_buzzer.c
*
* Programa de generación de sonidos empleando la libreria BUZZER.h
*
* Created: 10/05/2021 10:38:32
* Author : Santiago Mas
*/

#include <avr/io.h>
#include <avr/delay.h>

#include "BUZZER.h"


int main(void)
{
	
	//-------------------- CONFIGURACION DE PUERTOS ----------------
	BUZZER_init_port();
	
	//------------------ BUCLE PRINCIPAL ---------------------------
	while (1)
	{
		BUZZER_play_note(1, NOTE_SOL);
	}
}

