/*
 * longdelay.c
 *
 *  Created on: 28-02-2018
 *      Author: psm8
 */

#include"longdelay.h"

void longdelay(int t)
{
	for(int i=0; i<t; i++)
		_delay_ms(1);
}
