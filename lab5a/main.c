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
	sei();
	USART_init(11);

	while(1)
	{
		USART_send(USART_receive());

	}
}
