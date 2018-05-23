/*
 * LCD.h
 *
 *  Created on: 14-03-2018
 *      Author: psm8
 */

#ifndef LAB11A_LCD_H_
#define LAB11A_LCD_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define LCD_PORT PORTA
#define LCD_DDR DDRA
#define LCD_E 3
#define LCD_RS 2

void lcdinit();
void lcd_write_instr(uint8_t data);
void lcd_clear();
void lcd_write_data(uint8_t);
void lcd_set_xy(uint8_t, uint8_t);
void lcd_write_text_xy(uint8_t, uint8_t, char* text);
void lcd_write_text_P(const char* text);


#endif /* LAB11A_LCD_H_ */

