/*
 * main.c
 *
 *  Created on: 28-03-2018
 *      Author: psm8
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include "rs232.h"


int main(void)
{
	DDRC = 0xFF;
	USART_init(5);
	sei();
	USART_send("hello\n");
	while(1)
	{
		if(znak == 'x')
		{
			USART_send("ok\n");
			znak = 0;
		}
		if(rxEnd==1)
		{
			if(strncmp((void*)bufforRead,"on",2))
			{
				USART_send("on\n");
//				PORTC = 0;
//				rxEnd = 0;
//				indeks = 0;
			}
//			if(strncmp((void*)bufforRead,"off",3))
//			{
//				USART_send("off\n");
//				PORTC = 0xff;
//				rxEnd = 0;
//				indeks = 0;
//			}
		}
	}
}