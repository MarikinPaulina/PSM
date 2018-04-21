/*
 * i2c.h
 *
 *  Created on: 20-04-2018
 *      Author: psm8
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#define ACK 1
#define NO_ACK 0

void I2C_init(void);
uint8_t I2C_start(void);
void I2C_stop(void);
uint8_t I2C_write(uint8_t byte);
uint8_t I2C_read(uint8_t *value, uint8_t ack);

#endif /* I2C_H_ */
