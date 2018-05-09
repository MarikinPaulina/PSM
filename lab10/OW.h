/*
 * ow.h
 *
 *  Created on: 09-05-2018
 *      Author: psm8
 */

#ifndef OW_H_
#define OW_H_

#include <avr/io.h>
#include <util/delay.h>

#define delA 6
#define delB 64
#define delC 60
#define delD 10
#define delE 9
#define delF 55
#define delG 0
#define delH 480
#define delI 70
#define delJ 410

#define OW_PIN PB3
#define OW_DIR DDRB
#define OW_OUT PORTB
#define OW_IN PINB

#define OW_low   OW_DIR |= 1 << OW_PIN
#define OW_high  OW_DIR &= ~( 1 << OW_PIN )
#define OW_check ( OW_IN & ( 1 << OW_PIN ) )

uint8_t OW_reset(void);
void    OW_send(uint8_t byte);
uint8_t OW_recv(void);
void    OW_send_bit(uint8_t bit);
uint8_t OW_recv_bit(void);


#endif /* OW_H_ */
