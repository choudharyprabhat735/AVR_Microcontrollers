#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRD = 0x0F; // Set PD0 to PD3 as output for motor control, PD4 to PD7 as input for buttons

    while(1)
    {
        PORTD = 0x00; // Turn off all motor outputs initially

        // Button 1 pressed (PD4 == 0)
        if((PIND & 0x10) == 0)
        {
            // Both motors clockwise
            // Motor A: IN1=1 (PD0), IN2=0 (PD1)
            // Motor B: IN3=1 (PD2), IN4=0 (PD3)
            PORTD = 0x05; // 00000101
            _delay_ms(500);
        }

        // Button 2 pressed (PD5 == 0)
        if((PIND & 0x20) == 0)
        {
            // Motor A clockwise, Motor B anti-clockwise
            // Motor A: IN1=1 (PD0), IN2=0 (PD1)
            // Motor B: IN3=0 (PD2), IN4=1 (PD3)
            PORTD = 0x09; // 00001001
            _delay_ms(500);
        }

        // Button 3 pressed (PD6 == 0)
        if((PIND & 0x40) == 0)
        {
            // Motor A anti-clockwise, Motor B clockwise
            // Motor A: IN1=0 (PD0), IN2=1 (PD1)
            // Motor B: IN3=1 (PD2), IN4=0 (PD3)
            PORTD = 0x06; // 00000110
            _delay_ms(500);
        }

        // Button 4 pressed (PD7 == 0)
        if((PIND & 0x80) == 0)
        {
            // Both motors anti-clockwise
            // Motor A: IN1=0 (PD0), IN2=1 (PD1)
            // Motor B: IN3=0 (PD2), IN4=1 (PD3)
            PORTD = 0x0A; // 00001010
            _delay_ms(500);
        }
    }
}
