/*
 * termo.h
 *
 *  Created on: 09-05-2018
 *      Author: psm8
 */

#ifndef TERMO_H_
#define TERMO_H_

#include "OW.h"

uint8_t DS18B20_init(void);
uint8_t DS18B20_start(void);
uint16_t DS18B20_read(void);

#endif /* TERMO_H_ */
