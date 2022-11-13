/*
 * GSM_Test.c
 *
 * Created: 10/30/2022 7:08:39 PM
 * Author : Kashyapa
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#define  UBRR_VALUE ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

//#include "Gsm.h"
//#include "Keypad.h"

void init_hardware(void);
void unlock_door (void);
void USART_Transmit(unsigned char data );
unsigned char receive_USART(void);
void senddata(char string[16]);
void USART_Init();
void sendSMS();

int main(void)
{
	init_hardware();
	PORTK |= 0B00000001; // give values for port K
	USART_Init();
	unlock_door();
	while (1)
	{
	}
}
void init_hardware(void)
{
	DDRK |= 0B00000011; // set the k port pins as output
}
void unlock_door(void)
{
	if (1) // AFTER completing all part in the code should add function name(password matching like that)
	{
		PORTK |= 0B00000010; // set pin 2 of port K high (unlock the door)
		sendSMS();
	}
	else
	{
		PORTK &= 0B11111101; // set pin 2 of port K high (still locked)
	}
}

void USART_Transmit(unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char receive_USART(void)
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}


void USART_Init()
{
		UBRR0H = (unsigned char)(UBRR_VALUE>>8);
		UBRR0L = (unsigned char)(UBRR_VALUE);
		UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
		UCSR0C = (3<<UCSZ00);
}

void senddata(char string[16])
{
	int length,count;
	length = strlen(string);

	for (count=0;count<length;count++)
	{
		USART_Transmit(string[count]);
	}
}

void sendSMS()
{	
	senddata("+94718799794");  //Enter the Mobile number
	USART_Transmit(34);
	USART_Transmit(13);
	USART_Transmit(10);
	_delay_ms(1000);
	
	senddata("Alert: Somebody trying to open");
	USART_Transmit(13);
	USART_Transmit(10);
	_delay_ms(1000);
}
