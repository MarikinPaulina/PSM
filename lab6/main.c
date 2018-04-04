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

volatile uint16_t liczba = 20;
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream)
{
lcd_write_data(c);
return 0;
}

ISR(TIMER1_COMPA_vect)
{
	SS_ENABLE();
	TransferSPI(1);
	TransferSPI(0xA0);
	liczba = (SPDR & 0x0f)<<8;
	TransferSPI(0);
	liczba |= SPDR;
	SS_DISABLE();

}


int main()
{


	stdout = &mystdout;
	lcdinit();
	InitSPI();
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10);
	OCR1A = 17280;
	TIMSK |= (1<<OCIE1A);
	sei();
	int i = 0;
	double tab[10];
	double srednia;
	while(1)
	{
		lcd_set_xy(0,0);
		printf("%d",liczba);
		lcd_set_xy(1,0);
		double v = liczba* 5.0/4095.0;
		tab[i] = v;
		srednia = 0;
		for(int j =0; j<10; j++)
		{
			srednia += tab[j];
		}
		srednia /= 10;
		i++;
		if(i == 10) i = 0;
//		printf("U = %.3f  ",v);
		printf("U = %.3f  ",srednia);
	}
}
