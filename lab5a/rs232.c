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

void USART_init(uint8_t ubrr)
{
	/* prędkość transmisji */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;

	/* Format ramki: słowo=8bitów, 2 bity stopu */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);

	/* Włączenie odbiornika i nadajnika */
	UCSRB = (1<<RXEN)|(1<<TXEN);
}

void USART_wait_for_empty(void)
{
	while ( !( UCSRA & (1<<UDRE)) )
	;
}

void USART_send(char* text)
{
	USART_wait_for_empty();
	UDR = *text;
	bufforSend = ++text;
}

ISR(USART_RXC_vect)
{
	znak = UDR;
}

ISR(USART_TXC_vect)
{
	if(*bufforSend)
		UDR = *(bufforSend++);
}