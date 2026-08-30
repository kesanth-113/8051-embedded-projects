#include <reg51.h>

// SPI pins
sbit MOSI = P1^0;
sbit MISO = P1^1;
sbit SCK  = P1^2;
sbit CS   = P1^3;

// Small delay
void spi_delay(void)
{
    int i;
    for(i = 0; i < 10; i++);
}

// Send and receive one byte
unsigned char spi_transfer(unsigned char data)
{
    unsigned char i;
    unsigned char received = 0;

    for(i = 0; i < 8; i++)
    {
        // Send MSB first
        if(data & 0x80)
            MOSI = 1;
        else
            MOSI = 0;

        SCK = 1;
        spi_delay();

        received <<= 1;

        if(MISO)
            received |= 1;

        SCK = 0;
        spi_delay();

        data <<= 1;
    }

    return received;
}

// Write to SPI device
void spi_write(unsigned char data)
{
    CS = 0;
    spi_transfer(data);
    CS = 1;
}

// Read from SPI device
unsigned char spi_read(void)
{
    unsigned char data;

    CS = 0;
    data = spi_transfer(0xFF);
    CS = 1;

    return data;
}

void main(void)
{
    unsigned char val;

    CS = 1;

    // Write 0x55 to SPI device
    spi_write(0x55);

    // Read from SPI device
    val = spi_read();

    while(1);
}
