/*
 * main.c
 *
 *  Created on: 11-04-2018
 *      Author: psm8
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "longdelay.h"
#include "rs232.h"
#include "spi.h"
#include "i2c.h"
#include "rtc.h"
#include "LCD.h"


char* week_days[7] = {"Pon","Wt", "Sr", "Czw", "Pi", "Sob", "Nd" };

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);
static int uart_putchar(char c, FILE *stream)
{
lcd_write_data(c);
return 0;
}

ISR(INT0_vect){
	uint8_t h,m,s,day,date,month,year;

	rtc_get_time(&h, &m, &s);
	rtc_get_date(&day, &date, &month, &year);

	lcd_set_xy(0, 0);
	printf("Date: %02d/%02d/20%02d", date, month, year);
	lcd_set_xy(1,0);
	printf("Time: %02d:%02d:%02d", h, m, s);


}

int main (void){





//	lcd_init();


	lcdinit();

	stdout = &mystdout;
	I2C_init();

	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0);

	//rtc_init();

	rtc_control_reg(0,1,0,0);

	rtc_set_time(12,16,1,0,0);
	rtc_set_date(1,25,64,18);

	sei();

	while(1){ }
	return 0;
}
