#include <software_spi.h>
#include <Arduino.h>


#define DELAY_CYCLE() delayMicroseconds(_clock_uS)

Software_SPI::Software_SPI(int input_pin,
                           int output_pin,
                           int clock_pin,
                           int bit_order,
                           int clock_uS)
{

  _input_pin  = input_pin;
  _output_pin = output_pin;
  _clock_pin  = clock_pin;
  _bit_order  = bit_order;
  _clock_uS   = clock_uS;
  
  pinMode(_input_pin,  INPUT);
  pinMode(_output_pin, OUTPUT);
  pinMode(_clock_pin,  OUTPUT);

}

unsigned char Software_SPI::SPI_Send_Receive(unsigned char output)
{
  unsigned char input = 0;
  char bit_loop;

  for (bit_loop = 0; bit_loop < 8; bit_loop++)
  {
    digitalWrite(_clock_pin, 0);
    
    DELAY_CYCLE();
    
    if (_bit_order == MSB_FIRST)
    {
      digitalWrite(_output_pin, ((output & 0x80) > 0 ? 1 : 0));
      output = output << 1;
    }
    else 
    {
      digitalWrite(_output_pin, ((output & 0x01) > 0 ? 1 : 0));
      output = output >> 1;
    }
    
    digitalWrite(_clock_uS, 1);
    
    DELAY_CYCLE();
    
    input = input << 1;
    input |= digitalRead(_input_pin) > 0 ? 1 : 0;
  }
}