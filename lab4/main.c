/*
 * main.c
 *
 *  Created on: 21-03-2018
 *      Author: psm8
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define Led7Seg_cat PORTC
#define Led7Seg_cat_dir DDRC
#define Led7Seg_and PORTD
#define Led7Seg_and_dir DDRD

/* Polecenie 1

ISR(TIMER1_COMPA_vect)
{
	if(!(PIND&(1<<6)))
	{
		if(PORTC == 0)
			PORTC = 0xFF;
		else
			PORTC = 0;
	}
}
 END
 */

volatile uint16_t j,d,s,t;
volatile uint16_t liczba = 0;
volatile uint8_t digits_7seg[] = {~(0x3f),~(0x06),~(0x5b),~(0x4f),~(0x66),~(0x6d),~(0x7d),~(0x07),~(0x7f),~(0x6f)};

void led7seg(uint16_t liczba)
{
	j = digits_7seg[liczba%10];
	liczba /= 10;
	d = digits_7seg[liczba%10];
	liczba /= 10;
	s = digits_7seg[liczba%10];
	liczba /= 10;
	t = digits_7seg[liczba%10];
}

ISR(TIMER1_COMPA_vect)
{
	liczba++;
	if(liczba == 10000)
		liczba = 0;
}

ISR(TIMER0_COMP_vect)
{
	static uint8_t anoda = 0;
	Led7Seg_and |= 0x0f;
	switch(anoda)
	{
	case 0: Led7Seg_cat = j; break;
	case 1: Led7Seg_cat = d; break;
	case 2: Led7Seg_cat = s; break;
	case 3: Led7Seg_cat = t; break;
	}
	Led7Seg_and &= ~(1<<anoda);
	anoda++;
	anoda %= 4;
}



int main()
{
/* Polecenie 1
	DDRC = 0xFF;
	DDRD = 0;
	PORTD = 0xFF;
	TCCR1B |= (1<<3) | (1<<1) | (1<<0); //Ustalanie licznika
	OCR1A = 17280;
	TIMSK |= (1<<4);
	sei();
	PORTC = 0;

	while(1){}
	END
	*/



	Led7Seg_and_dir = 0x0F;
	Led7Seg_and = 0x0F;
	Led7Seg_cat_dir = 0xff;
	Led7Seg_cat = 0xff;
	TCCR0 |= (1<<WGM01) | (1<<CS02);
	OCR1A = 86;
	TIMSK |= (1<<OCIE0);
	TCCR1B |= (1<<3) | (1<<1) | (1<<0);
	OCR1A = 17280;
	TIMSK |= (1<<4);
	sei();

	while(1){
		led7seg(liczba);
	}

}
