/*
 * File:   udemy7segment.c
 * Author: PRABHAT
 *
 * Created on July 3, 2025, 4:58 PM
 */


/*#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
int  main(){
    uint8_t c[10] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
    DDRD = 0XFF;
    while(1){
        for (int i =0;i<10;i++){
            PORTD=c[i];
            _delay_ms(80);
        }
    }
}*/
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// Pattern for letter 'A'
uint8_t pattern[8] = {
    0x18, // 00011000
    0x24, // 00100100
    0x42, // 01000010
    0x42, // 01000010
    0x7E, // 01111110
    0x42, // 01000010
    0x42, // 01000010
    0x00  // 00000000
};

int main(void)
{
    DDRC = 0xFF; // Rows as output
    DDRD = 0xFF; // Columns as output

    while (1)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            PORTD = ~(1 << i);      // Enable one column at a time (active high)
            PORTC = pattern[i];     // Set rows for that column
            _delay_ms(2);           // Short delay for persistence
            PORTC = 0x00;           // Turn off all rows
        }
    }
}

