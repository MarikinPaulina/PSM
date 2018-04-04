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


const char tekst[] PROGMEM = "Hello World!";

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream)
{
lcd_write_data(c);
return 0;
}

int main()
{
	stdout = &mystdout;
	lcdinit();
	lcd_write_text_P(tekst);
	lcd_write_text_xy(1,7,'P');

	printf("%.2f %.2f",3.754, 5.24);


}
