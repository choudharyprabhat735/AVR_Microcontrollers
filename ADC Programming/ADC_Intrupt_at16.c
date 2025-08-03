/*
 * File:   ADC_Intrupt_at16.c
 * Author: PRABHAT
 *
 * Created on August 3, 2025, 12:12 PM
 */


#define F_CPU 8000000UL  // Define the clock frequency for delay

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Function to send command to LCD
void cmd(char a)
{
    PORTB = a;          // Send command byte to PORTB (connected to LCD data pins)
    PORTD |= 0x20;      // RS = 0 (command mode), EN = 1 (Enable high)
    _delay_ms(40);     
    PORTD &= 0x00;      // Clear all bits of PORTD (EN = 0, RS = 0)
}

// Function to send data (character) to LCD
void data(char a)
{
    PORTB = a;          // Send data byte to PORTC (connected to LCD data pins)
    PORTD |= 0xA0;      // RS = 1 (data mode), EN = 1 (Enable high)
    _delay_ms(40);
    PORTD &= 0xCF;      // Clear EN and RS bits (EN = 0, RS = 0)
    PORTD &= 0x80;      // Retain only PD7, clear lower bits (not strictly necessary)
}

// Function to display a string on LCD
void display(char *a)
{
    while((*a) != '\0') // Loop through each character until null terminator
    {
        data(*a);       // Send character to LCD
        a++;            // Move to next character
    }
}

// ADC Interrupt Service Routine
// ADC Interrupt Service Routine
ISR(ADC_vect)
{
    static uint16_t prev_adc_value = 0xFFFF;  // Initialize with invalid value (never matches initially)

    unsigned int adc_value, adc1, adch;

    // Read ADC result
    adc1 = ADCL;             
    adch = ADCH;             
    adc_value = (adch << 2) | (adc1 >> 6);

    // ? Only blink LED/buzzer when value changes
    if(adc_value != prev_adc_value)
    {
        PORTD |= 0x01;     // PD0 high ? LED/Buzzer ON
       _delay_ms(500);    
        PORTD &= ~0x01;    // OFF
        prev_adc_value = adc_value;  // Update stored value
    }

    cmd(0x80); 
    cmd(0xC0);  // Move LCD cursor

    // Display ADC value
    data((adc_value / 1000) + 0x30);              
    data(((adc_value % 1000) / 100) + 0x30);      
    data(((adc_value % 100) / 10) + 0x30);        
    data((adc_value % 10) + 0x30);                

    _delay_ms(500); 
    ADCSRA &= 0xEF;   // Clear interrupt flag
}


// Main function
int main()
{
    DDRA = 0x00;      // Set PORTA as input (for ADC input like potentiometer)
    DDRB = 0xFF;      // Set PORTB as output (for LCD data)
    DDRD = 0xFF;      // Set PORTD as output (LCD control lines + LED)

    // LCD Initialization
    cmd(0x38);        // Function set: 8-bit, 2 line, 5x8 dots
    cmd(0x80);        // Set DDRAM address to 0x00 (1st line start)
    cmd(0x01);        // Clear display
    cmd(0x0c);        // Display ON, cursor OFF
    display("ADC RAW O/P:"); // Display title/message on LCD

    while(1)
    {
        ADCSRA = 0xC8;   // Enable ADC, start conversion, enable ADC interrupt
                         // ADEN=1, ADSC=1, ADIE=1
        ADMUX = 0x60;    // Select ADC channel 0, use AREF as reference voltage
                         // ADLAR=1 (left-adjust result)
        sei();           // Enable global interrupts
    }
}

