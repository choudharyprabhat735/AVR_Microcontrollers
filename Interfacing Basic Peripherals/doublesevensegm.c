/*
 * File:   doublesevensegm.c
 * Author: PRABHAT
 *
 * Created on July 3, 2025, 10:41 AM
 */

#define F_CPU 1000000UL
#include <avr/io.h> 
#include <util/delay.h> 
int main() 
{ 
    int i=0,j=0,k=0;
    uint8_t a[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 
    DDRD = 0xFF; 
    DDRC = 0x03;
    while(1) 
    { 

        for(i=0;i<=9;i++) 
            { 
            for(j=0;j<=9;j++) 
            {
                for(k=0;k<100;k++)
                {
                    PORTC = 0x02;
                    PORTD = a[i];
                    _delay_ms(1);
                    
                    PORTC = 0x01;
                    PORTD = a[j];
                    _delay_ms(1); 
                    
                } 
            }
        }
    }
}
