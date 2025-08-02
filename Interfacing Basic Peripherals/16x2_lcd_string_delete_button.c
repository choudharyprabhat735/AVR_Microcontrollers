/*
 * File:   16x2_lcd_string_delete_button.c
 * Author: PRABHAT
 *
 * Created on July 14, 2025, 9:04 AM
 */


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void cmd(char a)// takaing character as a parameter
{
    PORTB = a;
    PORTD = 0x20; // RS = 0,RW=0 EN=1
    _delay_ms(2); // little delay to work 
    PORTD = 0x00; // TURN OFF ENABLE PIN
}

void data(char a)
{
    PORTB = a;
    PORTD = 0xA0; // RS = 1,RW= 0,EN=1.
    _delay_ms(2); // little delay to work
    PORTD = 0X80; // TURN OFF ENABLE PIN SO THAT NO FURTHER DATA IT ACCEPTS  
}

void display (char *a)
{
    while((*a) != '\0')
    {
        data(*a);
        a++;
    }
}

void delete ()
{
    cmd(0x10);
    data(' ');
    cmd(0x10);
    
}

int main()
{
    DDRB = 0xFF; //all pins of portc are output pins
    DDRD = 0xE0; //PD 7,PD 6 , PD 6 also as output pin as control pin of lcd.
    PORTB = 0x00; 
    PORTD = 0x00;// initialize both port c and d as zero.
    cmd(0x38); // initialize lcd in 8 bit mode and activate both rows.
    cmd(0x80); // cursor will fore to come in startig position of first row.
    cmd(0x01); // clearing the lcd screen
    cmd(0x0E); // turning on the display and enable cursor blinkiing
    cmd(0x06); // telling the lcd to automatically increment the cursor while displaying data.
    display("Prabhat"); 
    while(1)
    {
        if (PIND & 0x01)
{
    _delay_ms(2); 
    if (PIND & 0x01) 
    {
       // delete();
        while (PIND & 0x01); 
        {
            delete();
        }
    }
}

    }
}