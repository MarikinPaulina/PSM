/*
 * main.c
 *
 *  Created on: 28-03-2018
 *      Author: psm8
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include "rs232.h"

ISR(TIMER1_COMPA_vect)
{
	if(!(PINB&(1<<6)))
	{
		if(PORTC == 0)
			PORTC = 0xFF;
		else
			PORTC = 0;
	}
}

int main(void)
{
	DDRC = 0xFF;
	DDRB = 0;
	PORTB = 0xFF;
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10);
	OCR1A = 17280;
	TIMSK |= (1<<4);
	sei();

	USART_init(5);
	USART_send("hello\n");
	while(1)
	{
//		if(znak == 'x')
//		{
//			USART_send("ok\n");
//			znak = 0;
//		}
		if(rxEnd==1)
		{
			if(strncmp((void*)bufforRead,"on",2)==0)
			{
				USART_send("on\n");
				PORTC = 0;
				rxEnd = 0;
				indeks = 0;
			}
			if(strncmp((void*)bufforRead,"off",3)==0)
			{
				USART_send("off\n");
				PORTC = 0xff;
				rxEnd = 0;
				indeks = 0;
			}
		}
	}
}
