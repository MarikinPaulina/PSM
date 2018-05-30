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
#include "LCD_timedate.h"


char* week_days[7] = {"Pon","Wt", "Sr", "Czw", "Pi", "Sob", "Nd" };
volatile uint8_t h,m,s,day,date,month,year;
volatile uint8_t alarm_h,alarm_m;
volatile uint8_t level,poziom;

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);
static int uart_putchar(char c, FILE *stream)
{
lcd_write_data(c);
return 0;
}

ISR(INT0_vect){
	rtc_get_time(&h, &m, &s);
	rtc_get_date(&day, &date, &month, &year);
}

int main (void){
//	Bzyczek
	DDRD |= (1<<0);
	PORTD |= (1<<0);

//	Przyciski
	DDRB &= ~( (1<<0) | (1<<1) | (1<<2) | (1<<3) );
	PORTB |= ( (1<<0) | (1<<1) | (1<<2) | (1<<3) );

//	Diody
	DDRD |= (1<<7) | (1<<6);
	DDRC |= (1<<2) | (1<<3);
	PORTD |= (1<<7) | (1<<6);
	PORTC |= (1<<2) | (1<<3);

	lcdinit();
	stdout = &mystdout;
	I2C_init();
	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0);

	rtc_control_reg(0,1,0,0);

	rtc_set_time(0,37,19,0,0);
//	rtc_set_date(3,30,5,18);

	sei();

	uint8_t alarm = 0;
	uint8_t set = 0;

	while(1){
		if(alarm)
		{

		}
		else
		{
			if(!(PINB&(1<<0)))
			{
				set++;
				if(set == 9)
					set = 0;
			}
			if(set == 0)
			{
				print_date(date,month,year,h,m,s);
			}
			if(set == 1)
			{
				print_date(date,month,year,h,m,s);
				_delay_ms(500);
				print_date_day(date,month,year,h,m,s);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					date--;
					if(date == 0)
						date = 31;
					tc_set_date(day,date,month,year);
				}
				if(!(PINB&(1<<2)))
				{
					date++;
					if(date == 32)
						date = 1;
					tc_set_date(day,date,month,year);
				}

			}
			if(set == 2)
			{
				print_date(date,month,year,h,m,s);
				_delay_ms(500);
				print_date_month(date,month,year,h,m,s);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					month--;
					if(month == 0)
						month = 12;
					tc_set_date(day,date,month,year);
				}
				if(!(PINB&(1<<2)))
				{
					month++;
					if(month == 13)
						month = 1;
					tc_set_date(day,date,month,year);
				}

			}
			if(set == 3)
			{
				print_date(date,month,year,h,m,s);
				_delay_ms(500);
				print_date_year(date,month,year,h,m,s);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					year--;
					if(year == 255)
						year = 99;
					tc_set_date(day,date,month,year);
				}
				if(!(PINB&(1<<2)))
				{
					year++;
					if(year == 100)
						year = 0;
					tc_set_date(day,date,month,year);
				}

			}
			if(set == 4)
			{
				print_date(date,month,year,h,m,s);
				_delay_ms(500);
				print_date_h(date,month,year,h,m,s);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					h--;
					if(h == 255)
						h = 23;
					rtc_set_time(s,m,h,0,0);
				}
				if(!(PINB&(1<<2)))
				{
					h++;
					if(h == 25)
						h = 0;
					rtc_set_time(s,m,h,0,0);
				}

			}
			if(set == 5)
			{
				print_date(date,month,year,h,m,s);
				_delay_ms(500);
				print_date_m(date,month,year,h,m,s);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					m--;
					if(m == 255)
						m = 59;
					rtc_set_time(s,m,h,0,0);
				}
				if(!(PINB&(1<<2)))
				{
					m++;
					if(m == 60)
						m = 0;
					rtc_set_time(s,m,h,0,0);
				}

			}
			if(set == 6)
			{
				print_date(date,month,year,h,m,s);
				_delay_ms(500);
				print_date_m(date,month,year,h,m,s);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					m--;
					if(m == 255)
						m = 59;
					rtc_set_time(s,m,h,0,0);
				}
				if(!(PINB&(1<<2)))
				{
					m++;
					if(m == 60)
						m = 0;
					rtc_set_time(s,m,h,0,0);
				}

			}

		}
	}
	return 0;
}
