/*
 * main.c
 *
 *  Created on: 21-02-2018
 *      Author: psm8
 */

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0b00100000;

	while(1)
	{
		PORTA = 0b00100000;
		_delay_ms(100);
		PORTA = 0b00000000;
		_delay_ms(400);
		PORTA = 0b00100000;
		_delay_ms(400);
		PORTA = 0b00000000;
		_delay_ms(100);
		PORTA = 0b00100000;
		_delay_ms(200);
		PORTA = 0b00000000;
		_delay_ms(200);
	}
}
