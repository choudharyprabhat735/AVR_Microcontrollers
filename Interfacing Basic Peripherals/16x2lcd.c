/*
 * File:   16x2lcd.c
 * Author: PRABHAT
 *
 * Created on July 7, 2025, 9:51 AM
 */


//#define F_CPU 1000000UL

//#include <avr/io.h>
//#include <util/delay.h>

/*void lcd_cmd(char cmd){
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
int main()
{
    PORTD = 0XFF;
    DDRC = 0XFF;
    lcd_cmd(0x01);
    lcd_cmd(0x02);
    lcd_cmd(0x06);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    while(1){
        lcd_cmd(0x80);
        lcd_data('A');
                _delay_ms(1000);
    }
}
*/












#define F_CPU 1000000UL


#include <avr/io.h>
#include <util/delay.h>

void lcd_cmd(char cmd){
    PORTD = cmd;
    PORTB &= ~0x01;  
    PORTB &= ~0x02;  
    PORTB |= 0x04;   
    _delay_ms(5);
    PORTB &= ~0x04;  
    _delay_ms(5);
}

void lcd_data(char data){
    PORTD = data;
    PORTB |= 0x01;   
    PORTB &= ~0x02;  
    PORTB |= 0x04;   
    _delay_ms(5);
    PORTB &= ~0x04;  
    _delay_ms(5);
}

int main() {
    DDRD = 0xFF;     
    DDRB = 0xFF;     
    lcd_cmd(0x01);   
    lcd_cmd(0x02);   
    lcd_cmd(0x06);   
    lcd_cmd(0x38);   
    lcd_cmd(0x0C);   
    while(1){
         
            for (int pos = 0; pos <=16; pos++) {
            lcd_cmd(0x01);                 
            lcd_cmd(0x80 + pos);           
            lcd_data('A');                
            _delay_ms(200); }
            
            for (int pos = 16; pos >=0; pos--) {
            lcd_cmd(0x01);                 
            lcd_cmd(0xC0 + pos);           
            lcd_data('A');                
            _delay_ms(200);}
    }
}
