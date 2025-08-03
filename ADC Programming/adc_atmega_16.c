/*
 * File:   adc_atmega_16.c
 * Author: PRABHAT
 *
 * Created on July 15, 2025, 9:49 AM
 */


#define F_CPU 8000000UL
#include<stdio.h>
#include <avr/io.h>
#include <util/delay.h>

void lcd_cmd(char cmd){
    PORTD = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0X02;
    PORTC |= 0X04;
    _delay_ms(5);
    PORTC &= ~0X04;
    _delay_ms(5);
}
void lcd_data(char data){
    PORTD = data;
    PORTC |= 0x01;
    PORTC &= ~0X02;
    PORTC |= 0x04;
    _delay_ms(5);
    PORTC &= ~0X04;
   _delay_ms(5);
}
void adc_init()
{
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN)|(1 << ADPS0)|(1 << ADPS1);
}
int adc_read(int channel)
{
    ADMUX = (1 << REFS0)|(channel);
    ADCSRA |= (1 << ADSC);
    while((ADCSRA & (1 << ADIF))==0);
    char data = ADC;
    return data;
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
    PORTA = 0X01;
    PORTD = 0XFF;
    DDRC = 0XFF;
    lcd_cmd(0x01);
    lcd_cmd(0x02);
    lcd_cmd(0x06);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    adc_init();
    char str[10];
    while(1)
    {
        _delay_ms(100);
        int data = adc_read(0);
        sprintf(str,"ADC value %d ",data);
        lcd_cmd(0x80);
        lcd_string(str);
    }
}