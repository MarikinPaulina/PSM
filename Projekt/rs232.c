/*
 * rs232.c
 *
 *  Created on: 28-03-2018
 *      Author: psm8
 */


#include "rs232.h"

volatile uint8_t znak;
volatile char *bufforSend;
volatile char bufforRead[MAXSIZE];
volatile uint8_t rxEnd;
volatile uint8_t indeks;
volatile uint8_t transmisja=0;

void USART_init(uint8_t ubrr)
{
	/* prędkość transmisji */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;

	/* Format ramki: słowo=8bitów, 2 bity stopu */
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(3<<UCSZ0);

	/* Włączenie odbiornika i nadajnika */
	UCSRB |= (1<<RXEN)|(1<<TXEN) | (1<<RXCIE) | (1<<TXCIE);
}

void USART_wait_for_empty(void)
{
	while ( !( UCSRA & (1<<UDRE)) )
	;
}

void USART_send(char* text)
{
	while(transmisja);
	USART_wait_for_empty();
	transmisja = 1;
	UDR = *text;
	bufforSend = ++text;
}


ISR(USART_RXC_vect)
{
	znak = UDR;
//	zad2
	if(indeks >= (MAXSIZE-1))
		indeks=0;
	bufforRead[indeks]=znak;
	indeks++;
	if(znak == '\n')
		rxEnd=1;
	else
		rxEnd=0;
}

ISR(USART_TXC_vect)
{
	if(*bufforSend)
		UDR = *(bufforSend++);
	else
		transmisja = 0;
}
