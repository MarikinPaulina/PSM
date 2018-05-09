/*
 * termo.c
 *
 *  Created on: 09-05-2018
 *      Author: psm8
 */

#include "termo.h"

uint8_t DS18B20_init(void)
{
	OW_reset(); //Autokonfiguracja
	return OW_reset(); //Zwrócenie statusu
}

uint8_t DS18B20_start(void)
{
	if( OW_reset() ) return 1; //nie ok
	OW_send(0xCC); //Pomiń ROM
	OW_send(0x44); //Konwersja temperatury
	while(!OW_check);
	return 0; //ok
}

uint16_t DS18B20_read(void)
{
	OW_reset();
	uint16_t temperature;
	OW_send(0xCC); //Pomiń ROM
	OW_send(0xBE);
	temperature = OW_recv();
	temperature |= ( (uint16_t) OW_recv()) << 8;
	return temperature;
}
