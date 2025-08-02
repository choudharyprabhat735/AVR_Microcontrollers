/*
 * File:   Uart_at16.c
 * Author: PRABHAT
 *
 * Created on August 2, 2025, 2:34 PM
 */


#define F_CPU 8000000UL   // Define the CPU frequency as 8 MHz (required for _delay_ms)

#include <avr/io.h>       // Include AVR I/O definitions
#include <util/delay.h>   // Include delay functions

// Function to transmit a single character via UART
void transmit(char a)
{
    UDR = a;                         // Load the character into UART Data Register for transmission
    while ((UCSRA & 0x40) == 0);     // Wait until transmission is complete (TXC flag in UCSRA becomes 1)
    _delay_ms(100);                  // Optional delay after transmission
}

int main()
{
    DDRD = 0x02;       // Set PD1 (TXD pin) as output, rest as input (PD1 = 0000 0010)
    PORTD = 0x00;      // Clear PORTD

    UCSRA = 0x00;      // USART Control and Status Register A: default settings
    UCSRB = 0x18;      // Enable transmitter (TXEN=1) and receiver (RXEN=1) => 0x18 = 0001 1000
    UCSRC = 0x06;      // Set frame format: 8 data bits, 1 stop bit (UCSZ1=1, UCSZ0=1)
    
    UBRRH = 0x00;      // Set high byte of baud rate register
    UBRRL = 0x33;      // Set low byte for baud rate 9600 with 8 MHz clock (UBRR = 51 or 0x33)

    // Transmit characters one by one
    transmit('P');
    transmit('G');
    transmit('$');
    transmit('6');

    while (1);         // Infinite loop to keep the program running
}

