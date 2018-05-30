/*
 * rlc.h
 *
 *  Created on: 21-04-2018
 *      Author: psm8
 */

#ifndef RTC_H_
#define RTC_H_

#define DS1307_SLA 0b11010000
#define DS1307_SLA_W (DS1307_SLA + 0)
#define DS1307_SLA_R (DS1307_SLA + 1)

#define DS1307_SEC 0
#define DS1307_SEC_CH 7

#define DS1307_MIN 1
#define DS1307_HOUR 2
#define DS1307_HOUR_AMPM 5
#define DS1307_HOUR_2412 6 //Dwunastogodzinny
#define DS1307_DAY 3
#define DS1307_DATE 4
#define DS1307_MONTH 5
#define DS1307_YEAR 6

#define DS1307_CTRL 7
#define DS1307_CTRL_OUT 7
#define DS1307_CTRL_SQWE 4
#define DS1307_CTRL_RS1 1
#define DS1307_CTRL_RS0 0

#define DS1307_RAM_B 8
#define DS1307_RAM_E 0x3f

#define dec2bcd(x) ( ( ((x) / 10) << 4)  + ( (x) % 10) )
#define bcd2dec(x) ( ( ((x) >> 4)*10) + ((x) & 0x0f) )

void rtc_init(void);
void rtc_control_reg(uint8_t out, uint8_t sqwe, uint8_t rs1, uint8_t rs0);
void rtc_set_time(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t h12_h24,uint8_t PM_AM);
void rtc_set_date(uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void rtc_get_time(uint8_t *h, uint8_t *m, uint8_t *s);
void rtc_get_date(uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year);

#endif /* RTC_H_ */
