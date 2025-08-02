/*
 * File:   UART_LCD_16.c
 * Author: PRABHAT
 *
 * Created on August 2, 2025, 3:18 PM
 */


#define F_CPU 8000000UL   // Define the CPU frequency as 8 MHz for delay functions

#include <avr/io.h>       // Include AVR I/O header
#include <util/delay.h>   // Include delay utilities

// UART Receive Function: Waits until data is received and returns it
char receive()
{
    while((UCSRA & 0x80) == 0);  // Wait until the RXC (Receive Complete) flag is set
    return UDR;                 // Return the received character from UART Data Register
}

// LCD Command Function: Sends a command to the LCD
void cmd(char a)
{
    PORTC = a;      // Send command byte to PORTC (connected to LCD data pins)
    PORTD = 0x20;   // RS = 0 (Command), EN = 1 (Enable pulse), 0x20 = 0010 0000
    _delay_ms(100); // Wait for LCD to process
    PORTD = 0x00;   // EN = 0 (falling edge to latch command)
}

// LCD Data Function: Sends data (character) to the LCD
void data(char a)
{
    PORTC = a;      // Send data byte to PORTC
    PORTD = 0xA0;   // RS = 1 (Data), EN = 1 (Enable pulse), 0xA0 = 1010 0000
    _delay_ms(100); // Wait for LCD to process
    PORTD = 0x80;   // EN = 0 (falling edge to latch data), keep RS = 1
}

int main()
{
    char a;                 // Variable to store received character

    DDRC = 0xFF;            // Set PORTC as output (LCD data lines)
    DDRD = 0xE0;            // Set PD5, PD6, PD7 as output (LCD control lines: RS, RW, EN)
    PORTC = 0x00;           // Clear PORTC
    PORTD = 0x00;           // Clear PORTD

    // UART initialization
    UCSRA = 0x00;           // Default settings for UCSRA
    UCSRB = 0x18;           // Enable Transmitter and Receiver (TXEN=1, RXEN=1)
    UCSRC = 0x06;           // 8-bit data, 1 stop bit, no parity (UCSZ1=1, UCSZ0=1)
    UBRRH = 0x00;           // Baud rate high byte
    UBRRL = 0x33;           // Baud rate low byte for 9600 baud with 8 MHz clock

    // LCD initialization commands
    cmd(0x38);              // 2 lines, 5x8 matrix (Function set)
    cmd(0x80);              // Move cursor to beginning of first line
    cmd(0x01);              // Clear display
    cmd(0x0E);              // Display ON, cursor ON
    cmd(0x06);              // Increment cursor

    while(1)
    {
        a = receive();      // Receive a character from UART
        cmd(0x80);          // Move cursor to beginning of first line
        cmd(0x01);          // Clear the display
        data(a);            // Display the received character on LCD
    }
}
