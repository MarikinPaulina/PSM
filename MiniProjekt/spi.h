/*
 * spi.h
 *
 *  Created on: 04-04-2018
 *      Author: psm8
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

#define MOSI PB5 //5 lub 6
#define SCK PB7 //zegar do 7
#define SS PB4 //napiecie do 8
#define MISO PB6 //5 lub 6
// kanał 0 ma pin 2, tam trzeba podłączyć źródło

//powyższe są zdefiniowane w nocie katalogowej atmega 32 np.miso jako pb6

#define SS_ENABLE() {PORTB&= ~(1<<SS);}
#define SS_DISABLE() {PORTB|= (1<<SS);}



void InitSPI(void);
uint8_t TransferSPI(uint8_t);

#endif /* SPI_H_ */
