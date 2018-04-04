/*
 * main.c
 *
 *  Created on: 14-03-2018
 *      Author: psm8
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LCD.h"
#include "spi.h"

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream)
{
lcd_write_data(c);
return 0;
}

ISR(TIMER1_COMPA_vect)
{

}

int main()
{
	stdout = &mystdout;
	lcdinit();
	InitSPI();
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10);
	OCR1A = 17280;
	TIMSK |= (1<<4);
	sei();

	while(1)
	{

	}
}
