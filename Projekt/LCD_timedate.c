/*
 * LCD_timedate.c
 *
 *  Created on: 30-05-2018
 *      Author: psm8
 */

#include "LCD.h"
#include "LCD_timedate.h"

void print_date(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s)
{
	lcd_set_xy(0, 0);
	printf("Date: %02d/%02d/20%02d", date, month, year);
	lcd_set_xy(1,0);
	printf("Time: %02d:%02d:%02d", h, m, s);
}

void print_date_day(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s)
{
	lcd_set_xy(0, 0);
	printf("Date:   /%02d/20%02d", month, year);
	lcd_set_xy(1,0);
	printf("Time: %02d:%02d:%02d", h, m, s);
}

void print_date_month(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s)
{
	lcd_set_xy(0, 0);
	printf("Date: %02d/  /20%02d", date, year);
	lcd_set_xy(1,0);
	printf("Time: %02d:%02d:%02d", h, m, s);
}

void print_date_year(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s)
{
	lcd_set_xy(0, 0);
	printf("Date: %02d/%02d/20  ", date, month);
	lcd_set_xy(1,0);
	printf("Time: %02d:%02d:%02d", h, m, s);
}

void print_date_h(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s)
{
	lcd_set_xy(0, 0);
	printf("Date: %02d/%02d/20%02d", date, month, year);
	lcd_set_xy(1,0);
	printf("Time:   :%02d:%02d", m, s);
}

void print_date_m(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s)
{
	lcd_set_xy(0, 0);
	printf("Date: %02d/%02d/20%02d", date, month, year);
	lcd_set_xy(1,0);
	printf("Time: %02d:  :%02d", h, s);
}



void print_alarm(uint8_t alarm_h, uint8_t alarm_m)
{
	lcd_set_xy(0, 0);
	printf("Alarm:");
	lcd_set_xy(1,0);
	printf("%02d:%02d", alarm_h, alarm_m);
}

void print_alarm_h(uint8_t alarm_h, uint8_t alarm_m)
{
	lcd_set_xy(0, 0);
	printf("Alarm:");
	lcd_set_xy(1,0);
	printf("  :%02d", alarm_m);
}

void print_alarm_m(uint8_t alarm_h, uint8_t alarm_m)
{
	lcd_set_xy(0, 0);
	printf("Alarm:");
	lcd_set_xy(1,0);
	printf("%02d:  ", alarm_h);
}

void print_level(uint8_t level)
{
	lcd_set_xy(0, 0);
	printf("Poziom testu: %02d",level);
	if(level == 0)
	{
		lcd_set_xy(1,0);
		printf("dowolny przycisk");
	}
}
