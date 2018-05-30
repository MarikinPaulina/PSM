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
	alarm_h = 1;
//	Bzyczek
	DDRD |= (1<<0);
	PORTD |= (1<<0);

//	Przyciski
	DDRB &= ~( (1<<0) | (1<<1) | (1<<2) | (1<<3) );
	PORTB |= ( (1<<0) | (1<<1) | (1<<2) | (1<<3) );

//	Diody
	DDRC |= (1<<2) | (1<<3) | (1<<4) | (1<<5);
	PORTC |= (1<<2) | (1<<3) | (1<<4) | (1<<5);

	lcdinit();
	stdout = &mystdout;
	I2C_init();
	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0);

	rtc_control_reg(0,1,0,0);

	rtc_set_time(0,0,20,0,0);
	rtc_set_date(3,30,5,18);

	sei();

	uint8_t alarm = 0;
	uint8_t set = 0;
	uint8_t uklad;

//	srand(s);
//	uklad = rand() % 16;
//	PORTC &= ~((uklad & (0x0f))<<2);
//	printf("%02d",uklad);
	while(1){
	if(alarm)
		{
			PORTD &= ~(1<<0);
			if(poziom == 0)
			{
				while((PINB&0x0f)==15){}
				alarm = 0;
				PORTD |= (1<<0);
			}
			else
			{
				while(poziom)
				{
					srand(s);
					uklad = rand() % 16;
					PORTC &= ((uklad & (0x0f))<<2);
					printf("%02d",uklad);
					while((PINB&0x0f)!=uklad){}
					poziom--;
				}
				PORTC |= (1<<2) | (1<<3) | (1<<4) | (1<<5);
				alarm = 0;
				PORTD |= (1<<0);
			}
		}
		else
		{
			if((h==alarm_h) & (m==alarm_m) & (set==0))
			{
				alarm = 1;
				poziom = level;
			}
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
				lcd_clear();
				print_date(date,month,year,h,m,s);
				_delay_ms(500);
				print_date_day(date,month,year,h,m,s);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					date--;
					if(date == 0)
						date = 31;
					rtc_set_date(day,date,month,year);
				}
				if(!(PINB&(1<<2)))
				{
					date++;
					if(date == 32)
						date = 1;
					rtc_set_date(day,date,month,year);
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
					rtc_set_date(day,date,month,year);
				}
				if(!(PINB&(1<<2)))
				{
					month++;
					if(month == 13)
						month = 1;
					rtc_set_date(day,date,month,year);
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
					rtc_set_date(day,date,month,year);
				}
				if(!(PINB&(1<<2)))
				{
					year++;
					if(year == 100)
						year = 0;
					rtc_set_date(day,date,month,year);
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
				lcd_clear();
				print_alarm(alarm_h, alarm_m);
				_delay_ms(500);
				print_alarm_h(alarm_h, alarm_m);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					alarm_h--;
					if(alarm_h == 255)
						alarm_h = 23;
				}
				if(!(PINB&(1<<2)))
				{
					alarm_h++;
					if(alarm_h == 25)
						alarm_h = 0;
				}

			}
			if(set == 7)
			{
				lcd_clear();
				print_alarm(alarm_h, alarm_m);
				_delay_ms(500);
				print_alarm_m(alarm_h, alarm_m);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					alarm_m--;
					if(alarm_m == 255)
						alarm_m = 59;
				}
				if(!(PINB&(1<<2)))
				{
					alarm_m++;
					if(alarm_m == 60)
						alarm_m = 0;
				}

			}
			if(set == 8)
			{
				lcd_clear();
				print_level(level);
				_delay_ms(500);
				_delay_ms(500);
				if(!(PINB&(1<<1)))
				{
					level--;
					if(level == 255)
						level = 5;
				}
				if(!(PINB&(1<<2)))
				{
					level++;
					if(level == 6)
						level = 0;
				}

			}

		}
	}
	return 0;
}
