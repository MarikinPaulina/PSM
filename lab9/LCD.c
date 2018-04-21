/*
 * LCD.c
 *
 *  Created on: 14-03-2018
 *      Author: psm8
 */

#include "LCD.h"

void lcdinit()
{
	uint8_t i;

	LCD_DDR = 0xFF;
	LCD_PORT = 0;
	_delay_ms(50);
	LCD_PORT &= ~(1<<LCD_RS);
	for(i=0; i<3; i++)
	{
		LCD_PORT |= (1<<LCD_E);
		LCD_PORT = (LCD_PORT & 0b00001111) | 0b00110000;
		_delay_us(1);
		LCD_PORT &= ~(1<<LCD_E);
		_delay_ms(5);
	}
	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0b00001111) | 0b00100000;
	_delay_us(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_us(100);

	lcd_write_instr(0b00101000);
	lcd_write_instr(0b00001100);
	lcd_write_instr(0b00000110);
	lcd_clear();
}

void lcd_clear()
{
	lcd_write_instr(1);
	_delay_ms(2);
}

void lcd_write_instr(uint8_t data)
{
	LCD_PORT &= ~(1<<LCD_RS);
	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | (data & 0xf0);
	_delay_us(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_us(100);
	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | ((data & 0x0f) << 4);
	_delay_us(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_us(100);
}

void lcd_write_data(uint8_t data)
{
	LCD_PORT |= (1<<LCD_RS);
	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | (data & 0xf0);
	_delay_us(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_us(100);
	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | ((data & 0x0f) << 4);
	_delay_us(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_us(100);
}

void lcd_set_xy(uint8_t x,uint8_t y)
{
	lcd_write_instr(0x80+y+0x40*x);
}

void lcd_write_text_xy(uint8_t x,uint8_t y, char* text)
{
	lcd_set_xy(x,y);
	lcd_write_data(text);
}

void lcd_write_text_P(const char* text)
{
	register uint8_t ch;
	while( (ch = pgm_read_byte(text++)))
		lcd_write_data(ch);
}
