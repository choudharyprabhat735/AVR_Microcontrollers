/*
 * File:   arrayled.c
 * Author: PRABHAT
 *
 * Created on June 26, 2025, 9:58 AM
 */


#define  F_CPU    1000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(){
    DDRD = 0xFF;
    //int arr[]={0x01,0x02,0x04,0x08,0x10,0x20,0x20,0x40,0x80};
       // int size=sizeof(arr)/sizeof(arr[0]);
    while(1){
        
        for(int i=0;i<=8;i++){
            PORTD = 1<<i;
            _delay_ms(100);
        }
    }
}
