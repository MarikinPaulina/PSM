/*
 * rs232.h
 *
 *  Created on: 28-03-2018
 *      Author: psm8
 */

#ifndef LAB5A_RS232_H_
#define LAB5A_RS232_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#define MAXSIZE 32

extern volatile uint8_t znak;
extern volatile char *bufforSend;
extern volatile char bufforRead[MAXSIZE];
extern volatile uint8_t rxEnd;
extern volatile uint8_t indeks;

void USART_init(uint8_t ubrr);
void USART_wait_for_empty(void);
void USART_send(char* text);

#endif /* LAB5A_RS232_H_ */
