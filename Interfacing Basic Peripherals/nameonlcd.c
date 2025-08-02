/*
 * File:   nameonlcd.c
 * Author: PRABHAT
 *
 * Created on July 9, 2025, 9:30 AM
 */


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void lcd_cmd(char cmd)
{
    PORTD = cmd & 0xF0;
    PORTC &= ~0x01;
    PORTC &= ~0X02;
    PORTC |= 0x04;
    _delay_ms(1);
    PORTC &= ~0x04;
    _delay_ms(1);

    PORTD = (cmd << 4) & 0xF0;
    PORTC &= ~0x01;
    PORTC &= ~0X02;
    PORTC |= 0x04;
    _delay_ms(1);
    PORTC &= ~0x04;
    _delay_ms(1);
}

void lcd_data(char data)
{
    PORTD = data & 0xF0;
    PORTC |= 0x01;
    PORTC &= ~0X02;
    PORTC |= 0x04;
    _delay_ms(1);
    PORTC &= ~0x04;
    _delay_ms(1);

    PORTD = (data << 4) & 0xF0;
    PORTC |= 0x01;
    PORTC &= ~0X02;
    PORTC |= 0x04;
    _delay_ms(1);
    PORTC &= ~0x04;
    _delay_ms(1);
}

int main() {
    DDRD = 0xF0;
    DDRC = 0x07;
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);

    while(1)
    {
        lcd_cmd(0x80);
        lcd_data('A');
        _delay_ms(2000);
    }
}
 
