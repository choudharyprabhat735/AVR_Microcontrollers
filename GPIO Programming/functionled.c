/*
 * File:   functionled.c
 * Author: PRABHAT
 *
 * Created on June 30, 2025, 9:12 AM
 */


///#define  F_CPU 1000000UL
//#include <avr/io.h>
//#include <util/delay.h>


//void led_sequence() {
    //for (int i = 0; i <= 8; i++) {
        //PORTD = 1 << i;
        //_delay_ms(100);
   // }
//}

//int main() {
  //  DDRD = 0xFF;  

   // while (1) {
    //    led_sequence();  
  //  }
//}

#define  F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


void led_sequence(uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        PORTD = 1 << i;
        _delay_ms(100);
    }
}

int main() {
    DDRD = 0xFF;   

    while (1) {
        led_sequence(8);  
    }
}
