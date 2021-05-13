/*
* Test_buzzer.c
* 
* Programa de control de altavoz de robot 2WD MiniQ
*
* Created: 10/05/2021 11:28:14
*  Author: Santiago Mas
*/

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "BUZZER.h"


int main(void)
{
	//------------------ CONFIGURACION DE PUERTOS ----------------
	BUZZER_init_port();
	
	
	//------------------ BUCLE PRINCIPAL -------------------------
	while (1)
	{
		BUZZER_play_note(1, NOTE_DO);
		BUZZER_play_note(1, NOTE_RE);
		BUZZER_play_note(1, NOTE_MI);
		BUZZER_play_note(1, NOTE_FA);
		BUZZER_play_note(1, NOTE_SOL);
		BUZZER_play_note(1, NOTE_LA);
		BUZZER_play_note(1, NOTE_SI);
		BUZZER_play_note(1, NOTE_DO_UP);
		
	}
}