/*
 * File:   transmiter_uart.c
 * Author: PRABHAT
 *
 * Created on July 19, 2025, 10:46 AM
 */


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void uart_init(long baud)
{
    UBRRL = (((F_CPU)/(16 * baud))-1);
    UBRRH = (((F_CPU)/(16 * baud))-1)<<8;
    UCSRB = (1 << TXEN)|(1 << RXEN);
    UCSRC = (1 << URSEL)|(1 << UCSZ1)|(1 << UCSZ0);
     
}

void uart_txc(char data)
{
   UDR = data;
   while ((UCSRA & (1 << UDRE)) == 0);  
}

void uart_string(char *ptr)
{
    while(*ptr != '\0')
    {
        uart_txc(*ptr++);
    }
}

int main()
{
    
    uart_init(9600);
    while(1)
    {
        _delay_ms(1000);
        uart_string("HELLO ");
        _delay_ms(1000);
    }
}