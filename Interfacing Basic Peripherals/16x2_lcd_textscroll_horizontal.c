/*
 * File:   16x2_lcd_textscroll_horizontal.c
 * Author: PRABHAT
 *
 * Created on July 13, 2025, 3:59 PM
 */


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void cmd(char a)// takaing character as a parameter
{
    PORTC = a;
    PORTD = 0x20; // RS = 0,RW=0 EN=1
    _delay_ms(100); // little delay to work 
    PORTD = 0x00; // TURN OFF ENABLE PIN
}
void data(char a)
{
    PORTC = a;
    PORTD = 0xA0; // RS = 1,RW= 0,EN=1.
    _delay_ms(100); // little delay to work
    PORTD = 0X80; // TURN OFF ENABLE PIN SO THAT NO FURTHER DATA IT ACCEPTS 
}
void LCD_init()
{
    cmd(0x38);
    cmd(0x80);
    cmd(0x0E);
    cmd(0x06);
}
void display (char *a)
{
    while((*a) != '\0')
    {
        data(*a);
        a++;
    }
}
int main()
{
    DDRC = 0xFF; //all pins of portc are output pins
    DDRD = 0xE0; //PD 7,PD 6 , PD 6 also as output pin as control pin of lcd.
    PORTC = 0x00; PORTD = 0x03;
    LCD_init();
    display("PRABHAT");
    while(1)
    {
        while((PIND & 0x01) == 0)
        {
             cmd(0x1C);
             _delay_ms(100);
        }
        while((PIND & 0x02) == 0)
        {
            cmd(0x18);
            _delay_ms(100);
        }
   
}
}