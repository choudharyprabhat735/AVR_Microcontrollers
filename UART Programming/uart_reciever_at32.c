/*
 * File:   uart_reciever_at32.c
 * Author: PRABHAT
 *
 * Created on July 21, 2025, 11:29 AM
 */


/*
 * File:   uart_receiver_string_lcd.c
 * Author: PRABHAT
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void cmd(unsigned char cmd)
{
    PORTB = cmd;
    PORTD = 0x40;  
    _delay_ms(2);
    PORTD = 0x00;  
}

void data(unsigned char data_value)
{
    PORTB = data_value;
    PORTD = 0x60;  
    _delay_ms(2);
    PORTD = 0x20;  
}


void string(char *str)
{
    while (*str)
    {
        data(*str++);
    }
}

void lcd_init()
{
    DDRB = 0xFF;  
    DDRD |= (1 << 6) | (1 << 5) | (1 << 4); // PD6, PD5, PD4 as control pins EN, RS, RW

    cmd(0x38);  // 8-bit mode, 2 lines
    cmd(0x0C);  // Display ON, cursor OFF
    cmd(0x06);  // Auto-increment cursor
    cmd(0x01);  // Clear display
    _delay_ms(5);
}

void uart_init(long baud)
{
    UBRRL = (((F_CPU)/(16 * baud))-1);
     UBRRH = (((F_CPU)/(16 * baud))-1)<<8;
     UCSRB = (1 << TXEN)|(1 << RXEN);
     UCSRC = (1 << URSEL)|(1 << UCSZ1)|(1 << UCSZ0);
     
}

char uart_rxc()
{
    while (!(UCSRA & (1 << RXC))); // Wait until data received
    return UDR;
}

void uart_string(char *ptr)
{
    while(*ptr)
    {
        while (!(UCSRA & (1 << UDRE))); // Wait until buffer empty
        UDR = *ptr++;
    }
}

int main()
{
    lcd_init();
    uart_init(9600);

    char str[7] = {0};

    while (1)
    {
        for (int i = 0; i < 6; i++)
        {
            str[i] = uart_rxc();
        }
        str[6] = '\0'; 

        cmd(0x01);      
        cmd(0x80);     
        string(str);    
        uart_string(str); 

        _delay_ms(1000);
    }
}
