/*
 * File:   adc_atmega_8.c
 * Author: PRABHAT
 *
 * Created on July 16, 2025, 8:59 AM
 */


#define F_CPU 1000000UL
#include<stdio.h>
#include <avr/io.h>
#include <util/delay.h>

void lcd_cmd(char cmd){
    PORTD = cmd;
    PORTB &= ~0x01;
    PORTB &= ~0X02;
    PORTB |= 0X04;
    _delay_ms(5);
    PORTB &= ~0X04;
    _delay_ms(5);
}
void lcd_data(char data){
    PORTD = data;
    PORTB |= 0x01;
    PORTB &= ~0X02;
    PORTB |= 0x04;
    _delay_ms(5);
    PORTB &= ~0X04;
   _delay_ms(5);
}
void adc_init()
{
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN)|(1 << ADPS0)|(1 << ADPS1);
}
int adc_read(int channel)
{
    ADMUX = (1 << REFS0)| (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while((ADCSRA & (1 << ADIF))==0);
    ADCSRA |= (1 << ADIF);
    int data = ADC;
    return data;
    //return ADC;
}

void lcd_string(char *ptr)
{
    while(*ptr != '\0')
    {
        lcd_data(*ptr++);
    }
}
int main()
{
    
    adc_init();
    DDRD = 0XFF;
    DDRB = 0XFF;
    lcd_cmd(0x01);
    lcd_cmd(0x02);
    lcd_cmd(0x06);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    char str1[16];
    char str2[16];
    while(1)
    {
    int a = adc_read(0);
    int b = adc_read(1);
    float v = adc_read(0);
    float w = adc_read(1);
    char voltage1[16];
    char voltage2[16];
        sprintf(str1, "Value1 %d",adc_read(0));
        sprintf(str2, "Value2 %d",adc_read(1));
        sprintf(voltage1,"voltage1 %.2f",5*(v/1023));
        sprintf(voltage2,"voltage2 %.2f",5*(w/1023));
         lcd_cmd(0x01);           // Clear screen
        lcd_cmd(0x80);           // First line
        lcd_string(str1);
        lcd_cmd(0xC0);           // Second line
        lcd_string(voltage1);
        _delay_ms(1000);         // Delay to allow viewing

        lcd_cmd(0x01);           // Clear again
        lcd_cmd(0x80);           // First line
        lcd_string(str2);
        lcd_cmd(0xC0);           // Second line
        lcd_string(voltage2);
        _delay_ms(1000);         // Delay to allow viewing
    }
}
