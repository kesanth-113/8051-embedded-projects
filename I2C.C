#include <reg51.h>

sbit SDA = P1^0;
sbit SCL = P1^1;

void i2c_delay(void)
{
    unsigned int i;
    for(i = 0; i < 20; i++);
}

void i2c_start(void)
{
    SDA = 1;
    SCL = 1;
    i2c_delay();

    SDA = 0;
    i2c_delay();

    SCL = 0;
}

void i2c_stop(void)
{
    SDA = 0;
    SCL = 1;
    i2c_delay();

    SDA = 1;
    i2c_delay();
}

void i2c_write_byte(unsigned char data)
{
    unsigned char i;

    for(i = 0; i < 8; i++)
    {
        SDA = (data & 0x80) ? 1 : 0;

        SCL = 1;
        i2c_delay();

        SCL = 0;

        data <<= 1;
    }
}

void main(void)
{
    SDA = 1;
    SCL = 1;

    i2c_start();

    i2c_write_byte(0x48 << 1);   

    i2c_write_byte(0x00);        

    i2c_write_byte(0xFF);        

    i2c_stop();

    while(1);
}
