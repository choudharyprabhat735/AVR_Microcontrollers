/*
 * File:   adc_single_channel.c
 * Author: PRABHAT
 *
 * Created on July 16, 2025, 5:07 PM
 */


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void cmd(char a)// takaing character as a parameter
{
    PORTC = a;
    PORTD = 0x20; // RS = 0,RW=0 EN=1
    _delay_ms(2); // little delay to work 
    PORTD = 0x00; // TURN OFF ENABLE PIN
}

void data(char a)
{
    PORTC = a;
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

int main()
{
    int rv_adc = 0,k;
    double v_adc = 0.0;
    DDRA = 0x00; DDRC = 0xFF; DDRD = 0xFF;
    PORTA = 0x01; PORTC = 0x00; PORTD = 0x00;
    ADMUX = 0x60; ADCSRA = 0X87;
    cmd(0x38); cmd(0x80);
    cmd(0x01); cmd(0x0C);
    while(1)
    {
        ADCSRA |= 0x40;
        while((ADCSRA & 0x40) != 0);
        
        rv_adc = (ADCL >> 6) | (ADCH << 2);
        v_adc = (rv_adc * 5) / 1023.0;
        k = v_adc * 1000;
        
        display("RAW O/P: ");
        data((rv_adc / 1000)+ 48);
        data(((rv_adc / 100) % 10) + 48);
        data(((rv_adc / 10) % 10) + 48);
        data((rv_adc % 10) + 48); 
        cmd(0x80); cmd(0xC0);
        
        display("VOLTS: ");
        data((k / 1000) + 48); data('.');
        data(((k/100)% 10)+48);
        data(((k/10)% 10)+48);
        data((k % 10)+ 48);
        display(" V  ");
        cmd(0xC0); cmd(0x80);
    }
}
