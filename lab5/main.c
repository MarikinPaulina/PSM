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

	while(1)
	{
		void USART_init(115200);

	}
}
