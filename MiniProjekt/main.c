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
#include "longdelay.h"
#include <string.h>
#include "rs232.h"
#include "spi.h"
#include <stdlib.h>

volatile uint16_t liczba = 20;
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream)
{
lcd_write_data(c);
return 0;
}

int voltage_to_temp(double v)
{
	int temp = v*100;
	return temp;
}

ISR(TIMER1_COMPA_vect)
{
	SS_ENABLE();
	TransferSPI(1);
	TransferSPI(0xA0);
	liczba = (SPDR & 0x0f)<<8;
	TransferSPI(0);
	liczba |= SPDR;
	SS_DISABLE();
}

int main(void)
{
//	Konfiguracja pinów
	DDRC = 0xFF;
	DDRB |= (1<<0);
	PORTB |= (1<<0);
//

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

//	Przerwania dla spi
	InitSPI();
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10);
	OCR1A = 17280;
	TIMSK |= (1<<OCIE1A);
//

//	Inne zmienne
	int kroki = 0;
	int gdzie = 0;
	int delay = 30;
	int temperatura_doc = 30;
	int temperatura = 30;
	int rozpoznanie = 0;
	double v = 0;
//

//	Testy
	USART_send("hello\n");
	PORTC = 0b00001000;
	longdelay(delay);
	PORTC = 0b00000100;
	longdelay(delay);
	PORTC = 0b00000010;
	longdelay(delay);
	PORTC = 0b00000001;
	longdelay(delay);
//

	while(1)
	{
//	Obsługa LCD
	lcd_write_text_xy(0,0,' ');
	printf("%d",gdzie);

	lcd_write_text_xy(0,7,' ');
	printf("%d",temperatura);

	lcd_write_text_xy(1,7,' ');
	printf("%d",temperatura_doc);
//


//	Termometr
	v = liczba* 5.0/4095.0;
	temperatura = voltage_to_temp(v);
//
		if(rxEnd==1)
			{
				if(strncmp((void*)bufforRead,"M104",4)==0)
				{
					temperatura_doc = atoi((const char *) bufforRead + 5);
					rozpoznanie = 1;
				}
				if(strncmp((void*)bufforRead,"M105",4)==0)
				{
					char buffor[MAXSIZE];
					itoa(temperatura,buffor,10);
					USART_send(buffor);
					USART_send("\n");
					rozpoznanie = 1;
				}
				if(strncmp((void*)bufforRead,"G1",2)==0)
				{

					if(strncmp((void*)bufforRead+3,"X",1)==0)
					{
						kroki = atoi((const char *) bufforRead + 4);
						gdzie += kroki;
						int skok = 0;
						skok = strchr((void*)bufforRead, 'F');
						if(skok!=0)
						{
							delay = atoi((const char *) skok+1);
							skok = 0;
						}
						if(kroki < 0)
						{
							for(int i=kroki; i!=0; i++)
							{
								PORTC = 0b00001000;
								longdelay(delay);
								PORTC = 0b00000100;
								longdelay(delay);
								PORTC = 0b00000010;
								longdelay(delay);
								PORTC = 0b00000001;
								longdelay(delay);
							}
						}
						else
						{
							for(int i=0; i<kroki; i++)
							{
								PORTC = 0b00000001;
								longdelay(delay);
								PORTC = 0b00000010;
								longdelay(delay);
								PORTC = 0b00000100;
								longdelay(delay);
								PORTC = 0b00001000;
								longdelay(delay);
							}
						}
					}

					if(strncmp((void*)bufforRead+3,"F",1)==0)
					{
						delay = atoi((const char *) bufforRead + 4);
					}
					rozpoznanie = 1;
				}
				lcd_clear();
				lcd_set_xy(1,0);
				printf((void*)bufforRead);

				rxEnd = 0;
				indeks = 0;
				memset((void*)bufforRead,0,MAXSIZE);

				if(rozpoznanie == 1)
				{
					USART_send("ok\n");
					rozpoznanie = 0;
				}
				else USART_send("error\n");
				}

//		Dioda
		if((temperatura >= (temperatura_doc - 1)) & (temperatura <= (temperatura_doc + 1))) PORTB &= ~(1<<0);
		else PORTB |= (1<<0);

	}

}
