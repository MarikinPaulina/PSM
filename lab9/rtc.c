/*
 * rlc.c
 *
 *  Created on: 21-04-2018
 *      Author: psm8
 */

#include "i2c.h"
#include "rtc.h"




void rtc_init(void){
	I2C_start();
	I2C_write(DS1307_SLA_W);
	I2C_write(DS1307_SEC);
	I2C_write(0);   //CH bit of SEC must be 0 to start oscillator
	I2C_stop();
}


void rtc_control_reg(uint8_t out, uint8_t sqwe, uint8_t rs1, uint8_t rs0){
	I2C_start();
	I2C_write(DS1307_SLA_W);
	I2C_write(DS1307_CTRL);
	I2C_write((out<<DS1307_CTRL_OUT)|(sqwe<<DS1307_CTRL_SQWE)|(rs1<<DS1307_CTRL_RS1)|(rs0<<DS1307_CTRL_RS0));
	I2C_stop();

}
void rtc_set_time(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t h12_h24, uint8_t PM_AM){
	I2C_start();
	I2C_write(DS1307_SLA_W);
	I2C_write(DS1307_SEC);
	I2C_write(dec2bcd(seconds));
	I2C_write(dec2bcd(minutes));
	I2C_write( dec2bcd(hours) | (PM_AM<<DS1307_HOUR_AMPM) | (h12_h24<<DS1307_HOUR_2412));
	I2C_stop();

}

void rtc_set_date(uint8_t day, uint8_t date, uint8_t month, uint8_t year){
	I2C_start();
	I2C_write(DS1307_SLA_W);
	I2C_write(DS1307_DAY);
	I2C_write(dec2bcd(day&0x07));
	I2C_write(dec2bcd(date&0x1f));
	I2C_write(dec2bcd(month&0x0f));
	I2C_write(dec2bcd(year&0x7f));
	I2C_stop();

}
void rtc_get_time(uint8_t *h, uint8_t *m, uint8_t *s){
	uint8_t value;

	I2C_start();
	I2C_write(DS1307_SLA_W);
	I2C_write(DS1307_SEC);
	I2C_start();
	I2C_write(DS1307_SLA_R);
	I2C_read(&value,ACK);
	*s = bcd2dec(value&0x7f);
	I2C_read(&value,ACK);
	*m = bcd2dec(value&0x7f);
	I2C_read(&value,NO_ACK);
	*h = bcd2dec(value&0x3f);
	I2C_stop();

}

void rtc_get_date(uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year){
	uint8_t value;

	I2C_start();
	I2C_write(DS1307_SLA_W);
	I2C_write(DS1307_DAY);
	I2C_start();
	I2C_write(DS1307_SLA_R);
	I2C_read(day,ACK);
	I2C_read(&value, ACK);
	*date = bcd2dec(value);
	I2C_read(&value, ACK);
	*month = bcd2dec(value);
	I2C_read(&value,NO_ACK);
	*year = bcd2dec(value);
	I2C_stop();

}













//
//
//void rtc_init(void)
//{
//	I2C_start();
//	I2C_write(DS1307_SLA_W);
//	I2C_write(DS1307_SEC);
//	I2C_write(0);
//	I2C_stop();
//}
//
//void rtc_control_reg(uint8_t out, uint8_t sqwe, uint8_t rs1, uint8_t rs0)
//{
//	I2C_start();
//	I2C_write(DS1307_SLA_W);
//	I2C_write(DS1307_CTRL);
//	I2C_write(	(out << DS1307_CTRL_OUT) |
//				(sqwe << DS1307_CTRL_SQWE) |
//				(rs1 << DS1307_CTRL_RS1) |
//				(rs0 << DS1307_CTRL_RS0)
//				);
//	I2C_stop();
//}
//
//void rtc_set_time(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t h12_h24,uint8_t PM_AM)
//{
//	I2C_start();
//	I2C_write(DS1307_SLA_W);
//	I2C_write(DS1307_SEC);
//	I2C_write(dec2bcd(seconds));
//	I2C_write(dec2bcd(minutes));
//	I2C_write(	dec2bcd(hours) |
//				(PM_AM << DS1307_HOUR_AMPM) |
//				(h12_h24 << DS1307_HOUR_2412)
//				);
//	I2C_stop();
//}
//
//void rtc_set_date(uint8_t day, uint8_t date, uint8_t month, uint8_t year)
//{
//	I2C_start();
//	I2C_write(DS1307_SLA_W);
//	I2C_write(DS1307_DAY);
//	I2C_write(dec2bcd(day & 0x07));
//	I2C_write(dec2bcd(date & 0x1f));
//	I2C_write(dec2bcd(month & 0x0f));
//	I2C_write(dec2bcd(year & 0x7f));
//	I2C_stop();
//}
//
//void rtc_get_time(uint8_t *h, uint8_t *m, uint8_t *s)
//{
//	uint8_t value;
//
//	I2C_start();
//	I2C_write(DS1307_SLA_W);
//	I2C_write(DS1307_SEC);
//	I2C_start();
//	I2C_write(DS1307_SLA_R);
//	I2C_read(&value,ACK);
//	*s = bcd2dec(value & 0x7f);
//	I2C_read(&value,ACK);
//	*m = bcd2dec(value & 0x7f);
//	I2C_read(&value,ACK);
//	*h = bcd2dec(value & 0x3f);
//	I2C_stop();
//}
////
////void rtc_get_date(uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year)
////{
////	uint8_t value;
////
////	I2C_start();
////	I2C_write(DS1307_SLA_W);
////	I2C_write(DS1307_DAY);
////	I2C_start();
////	I2C_write(DS1307_SLA_R);
////	I2C_read(day,ACK);
////	I2C_read(&value,ACK);
////	*date = bcd2dec(value);
////	I2C_read(&value,ACK);
////	*month = bcd2dec(value);
////	I2C_read(&value,ACK);
////	*year = bcd2dec(value);
////	I2C_stop();
////}
//
//void rtc_get_date(uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year){
//
//	uint8_t value;
//
//	I2C_start();
//	I2C_write(DS1307_SLA_W);
//	I2C_write(DS1307_DAY);
//	I2C_start();
//	I2C_write(DS1307_SLA_R);
//	I2C_read(day,ACK);
//	I2C_read(&value, ACK);
//	*date = bcd2dec(value);
//	I2C_read(&value, ACK);
//	*month = bcd2dec(value);
//	I2C_read(&value, NO_ACK);
//	*year = bcd2dec(value);
//	I2C_stop();
//}
