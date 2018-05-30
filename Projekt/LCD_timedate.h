/*
 * LCD_timedata.h
 *
 *  Created on: 30-05-2018
 *      Author: psm8
 */

#ifndef LCD_TIMEDATAEH_
#define LCD_TIMEDATAEH_

void print_date(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s);
void print_date_day(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s);
void print_date_month(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s);
void print_date_year(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s);
void print_date_h(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s);
void print_date_m(uint8_t date, uint8_t month, uint8_t year, uint8_t h, uint8_t m, uint8_t s);

void print_alarm(uint8_t alarm_h, uint8_t alarm_m);
void print_alarm_h(uint8_t alarm_h, uint8_t alarm_m);
void print_alarm_m(uint8_t alarm_h, uint8_t alarm_m);

void print_level(uint8_t level);


#endif /* LCD_TIMEDATAEH_ */
