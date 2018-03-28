/*
 * buff.c
 *
 *  Created on: 07-03-2018
 *      Author: psm8
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DDR_LED DDRA
#define PORT_LED PORTA
#define PRZYCISK PD2
#define DDR_PRZYCISK DDRD
#define PORT_PRZYCISK PORTD

volatile uint8_t counter=0;

ISR(INT0_vect, ISR_BLOCK)
{
	counter++;
}

int main(void)
{
	//Wybór rodzaju portu
	DDR_LED=0xff;
	DDR_PRZYCISK&=~(1<<PRZYCISK);

	//Wstępne wyzerowanie diod - opcjonalne
	PORT_LED=255;

	//Podciagniecie rezystora do przycisku
	PORT_PRZYCISK|=(1<<PRZYCISK);

	//Konfuguracja przerwania
	MCUCR|=(1<<ISC01);
	GICR|=(1<<INT0);

	//Globalne włączenie przerwań
	sei();

	while(1) PORT_LED=~counter;

	return 0;
}
