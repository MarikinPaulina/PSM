/*
 * main.c
 *
 *  Created on: 28-02-2018
 *      Author: psm8
 */

#include <avr/io.h>
#include"longdelay.h"

int main()
{
	DDRC = 0xFF;
	DDRA = 0xFF;
	int x =30;
	DDRD = 0;
	PORTD = 0xFF;
	PORTC = 0xFF;
	while(1)
	{
		if(!(PIND&(1<<0)))
		{
			PORTC = 0;
			PORTA = 0b00000001;
			longdelay(x);
			PORTA = 0b00000010;
			longdelay(x);
			PORTC = 0xFF;
			PORTA = 0b00000100;
			longdelay(x);
			PORTA = 0b00001000;
			longdelay(x);
		}
		if(!(PIND&(1<<1)))
		{
			PORTC = 0;
			PORTA = 0b00001000;
			longdelay(x);
			PORTA = 0b00000100;
			longdelay(x);
			PORTC = 0xFF;
			PORTA = 0b00000010;
			longdelay(x);
			PORTA = 0b00000001;
			longdelay(x);
		}
	}

}


