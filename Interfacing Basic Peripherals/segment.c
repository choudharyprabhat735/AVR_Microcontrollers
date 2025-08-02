/*
 * File:   segment.c
 * Author: PRABHAT
 *
 * Created on July 5, 2025, 10:29 AM
 */
#define F_CPU 1000000UL




#include <avr/io.h> 
#include <util/delay.h>

int main() {
    DDRD = 0xFF;    
    DDRC = 0x00;    

    uint8_t arr[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
    int count = 0;

    while (1) 
    {
        
        if (PINC & 0x01) {
            count++;
            if (count > 7)
                count = 0;
            _delay_ms(300); 
            
             if (PINC & 0x02) {
            count--;
            if (count > 0)
                count = 7;
            _delay_ms(300);
        }
        PORTD = arr[count];
    }
}
}                                                                                                                                                             