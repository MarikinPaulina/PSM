/*
 * main.c
 *
 *  Created on: 11-04-2018
 *      Author: psm8
 */

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "rs232.h"
#include "spi.h"
#include "longdelay.h"
#include "OW.h"
#include "termo.h"

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream)
{
lcd_write_data(c);
return 0;
}

int main(void)
{
	int16_t temperature;

//	Włączenie termometru
	DS18B20_init();

//	Sterowanie z rs232
	USART_init(5);
	sei();
//

//	Włączenie LCD
	stdout = &mystdout;
	lcdinit();
//	lcd_write_text_xy(1,7,'P'); //Test
//	printf("%f",1.5); //Test
//

	while(1)
	{
		DS18B20_start();

		temperature = DS18B20_read();
		lcd_set_xy(0,0);
//		printf("Hello"); //Test
		printf("T = %5.1f\337C", ((double)temperature)*0.0625);
		lcd_set_xy(1,0);
		printf("T =%4d.%04d\337C", temperature>>4, (temperature & 0x0f) * 625);
	}

}
