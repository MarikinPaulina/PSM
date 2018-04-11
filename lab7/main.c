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
#include <stdlib.h>


#define WAVE 27647
#define MIN 0.9 //ms minimalny czas trwania
#define MAX 2.1 //ms maksymalny czas trwania
#define MID 1.5 //ms średni czas trwania

int convert_to_ocr1a(float x)
{
	//x: czas w milisekundach
	int OCR1A_value = x*WAVE/20;
	return OCR1A_value;
}

int angle_to_ocr1a(float angle_degrees)
{
	float time = 0.4 + angle_degrees/2/90.0 * (2.3 - 0.4) + MIN; //konwersja kąta na ms
//	float time = MID + angle_degrees/90 *(MAX-MIN); //konwersja kąta na ms ::TODO
	return convert_to_ocr1a(time);
//	int time = 2073 + angle_degrees/90*(2400-2073);
//	return time;
}



int main(void)
{
//	Inicjalizacja Pwm
//	TCCR1A
	TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	TCCR1A &= ~((1<<COM1A0) | (1<<WGM10));
//	TCCR1B
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11);
	TCCR1B &= ~((1<<CS12) | (1<<CS10));
//	Inne
	ICR1 = WAVE;
	DDRD |= (1<<5); // Pin D5 na wyjście
//	Koniec inicjalizacji Pwm

//	Dioda
//	TCCR0
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<COM00) | (1<<CS01);
	TCCR0 &= ~((1<<CS00) | (1<<CS02));
	int i = 1;
	OCR0 = 0;
	DDRB |= (1<<3); // Pin B3 na wyjście
//

//	Sterowanie z rs232
	USART_init(5);
	sei();
	int kat = 0;
	while(1)
	{
//		OCR1A = convert_to_ocr1a(MIN);
//		longdelay(1000);
//		OCR1A = convert_to_ocr1a(MID);
//		longdelay(1000);
//		OCR1A = convert_to_ocr1a(MAX);
//		longdelay(1000);

//		OCR1A = angle_to_ocr1a(90);
//		longdelay(1000);
//		OCR1A = angle_to_ocr1a(0);
//		longdelay(1000);
//		OCR1A = angle_to_ocr1a(-90);
//		longdelay(1000);

//		Dioda
		OCR0 += i;
		longdelay(11);
		if(OCR0 == (0xff - 1))
			i = -i;
		if(OCR0 == 0)
			i = -i;
//

		OCR1A = angle_to_ocr1a(kat);
		if(rxEnd==1)
		{
			if(strncmp((void*)bufforRead,"kat",3)==0)
			{
				kat = atof((const char *) bufforRead + 4);
//				kat = 90;
			}
			OCR1A = angle_to_ocr1a(kat);
			rxEnd = 0;
			indeks = 0;
			memset((void*)bufforRead,0,MAXSIZE);
		}
	}
}
