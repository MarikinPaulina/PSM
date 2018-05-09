/*
 * ow.c
 *
 *  Created on: 09-05-2018
 *      Author: psm8
 */

#include "OW.h"

uint8_t OW_reset(void)
{
	uint8_t result;
	_delay_us(delG);
	OW_low;
	_delay_us(delH);
	OW_high;
	_delay_us(delI);
	result = OW_check;
	_delay_us(delJ);
	return result;
}

void    OW_send_bit(uint8_t bit)
{
	if(bit==1)
	{
		OW_low;
		_delay_us(delA);
		OW_high;
		_delay_us(delB);
	}
	if(bit==0)
	{
		OW_low;
		_delay_us(delC);
		OW_high;
		_delay_us(delD);
	}
}

uint8_t OW_recv_bit(void)
{
	uint8_t result;
	OW_low;
	_delay_us(delA);
	OW_high;
	_delay_us(delE);
	result = OW_check;
	_delay_us(delF);
	return result;
}

void    OW_send(uint8_t byte)
{
	uint8_t i;
	for(i=0; i<8; i++)
	{
		OW_send_bit(byte & 0x01);
		byte >>= 1;
	}
}

uint8_t OW_recv(void)
{
	uint8_t i;
	uint8_t result = 0;
	for(i=0; i<8; i++)
	{
		result >>= 1;
		if(OW_recv_bit()) result |= 0x80;
	}
	return result;
}

//uint8_t OW_recv(void)
//{
//	uint8_t i;
//	uint8_t result = 0;
//	for(i=0; i<8; i++)
//	{
//		result >>= 1;
//		OW_low;
//		_delay_us(delA);
//		OW_high;
//		_delay_us(delE);
//		if(OW_check) result |= 0x80;
//		_delay_us(delF);
//	}
//	return result;
//}
