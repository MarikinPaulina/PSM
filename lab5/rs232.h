/*
 * rs232.h
 *
 *  Created on: 28-03-2018
 *      Author: psm8
 */

#ifndef RS232_H_
#define RS232_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define MAXSIZE 32;

void USART_init(uint8_t ubrr);
void USART_wait_for_empty(void);
void USART_send(char* text);

#endif /* RS232_H_ */
