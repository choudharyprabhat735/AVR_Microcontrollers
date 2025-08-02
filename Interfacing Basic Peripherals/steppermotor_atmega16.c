/*
 * File:   steppermotor_atmega16.c
 * Author: PRABHAT
 *
 * Created on August 1, 2025, 12:09 PM
 */


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRD = 0X0F; PORTD = 0X00;
    while(1)
    {
        for(int i = 0;i<128; i++)
        {
            PORTD = 0x01;    //coil one is active
            _delay_ms(3);
            PORTD = 0x02;   //coil 2 is active
            _delay_ms(3);
            PORTD = 0x04;   //coil 3 is active
            _delay_ms(3);
            PORTD = 0x08;   //coil 4 is active
            _delay_ms(3);
        }
        _delay_ms(1000);
    }
}
