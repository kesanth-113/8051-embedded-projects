#include <reg51.h>

// ADC0804 pins
sbit RD  = P3^0;
sbit WR  = P3^1;
sbit INTR = P3^2;
sbit CS  = P3^3;

unsigned char ADC_read() {
    unsigned char value;
    CS  = 0;
    WR  = 0;
    WR  = 1;         // start conversion
    while(INTR == 1); // wait for completion
    RD  = 0;
    value = P1;      // read ADC value
    RD  = 1;
    CS  = 1;
    return value;
}

void main() {
    unsigned char adc_val;
    P1 = 0xFF;       // P1 as input

    while(1) {
        adc_val = ADC_read();
        P2 = adc_val; // show on LEDs
    }
}
