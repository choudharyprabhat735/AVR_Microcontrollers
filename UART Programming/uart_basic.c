/*
 * File:   uart_basic.c
 * Author: PRABHAT
 *
 * Created on July 17, 2025, 10:02 AM
 */


#define F_CPU 8000000UL
#include<stdio.h>
#include <avr/io.h>
#include <util/delay.h>

void uart_init(long baud)
{
    UBRRL = (((F_CPU)/(16 * baud))-1);
     UBRRH = (((F_CPU)/(16 * baud))-1)<<8;
     UCSRB = (1 << TXEN)|(1 << RXEN);
     UCSRC = (1 << URSEL)|(1 << UCSZ1)|(1 << UCSZ0);
     
}

void uart_txc (char data)
{
    UDR = data;
    while((UCSRA & (1 << UDRE))==0);
}

char uart_rxc ()
{
    while((UCSRA & (1 << RXC)) == 0);  // Check UCSRA, not UCSRC
    return UDR;
}

    

int main()
{
    uart_init(9600);    
     

    while(1)
    {
        _delay_ms(100);
       char ch = uart_rxc();     
         uart_txc(ch);   
    }
}
