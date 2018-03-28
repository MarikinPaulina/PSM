/*
 * main.c
 *
 *  Created on: 07-03-2018
 *      Author: psm8
 */

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t i = 0xFF;

ISR(INT0_vect,ISR_BLOCK)
{
	i--;
}

int main()
{
	DDRC = 0xFF;
	DDRD = 0;
	PORTD = 0xFF;
	MCUCR |= (1<<1);
	GICR |= (1<<6);

	sei();
	while(1)
	{
		PORTC = i;
	}

}


