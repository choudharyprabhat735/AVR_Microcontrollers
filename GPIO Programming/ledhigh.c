/*
 * File:   ledhigh.c
 * Author: PRABHAT
 *
 * Created on June 23, 2025, 10:50 AM
 */

#define  F_CPU    1000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(){
    DDRD = 0xFF;
    while(1){
        PORTD = 0X01;
        //PORTD=0X00;
        _delay_ms(100);
        PORTD = 0X02;
        //PORTD=0X00;
         _delay_ms(100);
         PORTD = 0X04;
         //YPORTD=0X00;
         _delay_ms(100);
        
    }
}
//0 0 0 0 0 0 0 0 
          //1 1 1