/*
 * main.c
 *
 *  Created on: 21-02-2018
 *      Author: psm8
 */

#include <avr/io.h> //Biblioteka z nazwami bajtów i bitów w mikrokontrolerze
#include <util/delay.h> //Biblioteka z funkcjami czekania

int main()
{
	DDRA = 0b00100000; //W Porcie A bit 6 jest ustawiony na wyjście, a pozostałe na wejście

	while(1)
	{
		PORTA = 0b00100000; //W Porcie A na wyjście wystawiona jest 1 (na wejściu schowane oporniki podciągające)
		_delay_ms(100); //Opóźnienie 100 ms
		PORTA = 0b00000000; //W Porcie A na wyjście wystawiona jest 0 (na wejściu schowane oporniki podciągające)
		_delay_ms(400); //Opóźnienie 400 ms
		PORTA = 0b00100000; //W Porcie A na wyjście wystawiona jest 1 (na wejściu schowane oporniki podciągające)
		_delay_ms(400); //Opóźnienie 400 ms
		PORTA = 0b00000000; //W Porcie A na wyjście wystawiona jest 0 (na wejściu schowane oporniki podciągające)
		_delay_ms(100); //Opóźnienie 100 ms
		PORTA = 0b00100000; //W Porcie A na wyjście wystawiona jest 1 (na wejściu schowane oporniki podciągające)
		_delay_ms(200); //Opóźnienie 200 ms
		PORTA = 0b00000000; //W Porcie A na wyjście wystawiona jest 0 (na wejściu schowane oporniki podciągające)
		_delay_ms(200); //Opóźnienie 200 ms
	}
}
