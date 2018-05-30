/*
 * i2c.c
 *
 *  Created on: 20-04-2018
 *      Author: psm8
 */

#include "i2c.h"

void I2C_init(void){

	TWBR = 47; //66 for 14,745600 MHz gives about 100kHz TWI SCLK
}

uint8_t I2C_start(void){

	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	return (TWSR & 0xf8);
}
void I2C_stop(void){
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	while(!(TWCR & (1<<TWSTO)));
}
uint8_t I2C_write(uint8_t byte){
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return (TWSR & 0xf8);
}

uint8_t I2C_read(uint8_t *value, uint8_t ack){
	TWCR = (1<<TWINT) | (1<< TWEN) | (ack<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	*value = TWDR;
	return (TWSR & 0xf8);
}
