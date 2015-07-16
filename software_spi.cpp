#include <software_spi.h>
#include <Arduino.h>


#define DELAY_CYCLE() delayMicroseconds(_clock_uS)
#define CLOCK_HIGH() digitalWrite(_clock_pin, 1)
#define CLOCK_LOW() digitalWrite(_clock_pin, 0)
#define WRITE_BIT(x) digitalWrite(_output_pin, x)
#define READ_BIT() digitalRead(_input_pin)

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

void Software_SPI::reset()
{
  CLOCK_LOW();
  WRITE_BIT(0);
  
}

unsigned char Software_SPI::SPI_Send_Receive(unsigned char output)
{
  unsigned char input = 0;
  unsigned char temp;
  char bit_loop;
  
  CLOCK_LOW();
  
  for (bit_loop = 0; bit_loop < 8; bit_loop++)
  {

    /* Drive the output value for the slave device. Then wait the low
       half of the clock cycle. 
     */
    
    if (_bit_order == MSB_FIRST)
    {
      temp = ((output & 0x80) > 0 ? 1 : 0);
      
      WRITE_BIT(temp);
      
      output = output << 1;
    }
    else 
    {
      temp = ((output & 0x01) > 0 ? 1 : 0);
      
      WRITE_BIT(temp);
      
      output = output >> 1;
    }
    
    DELAY_CYCLE();
    
    /* Set the clock pin high; this will trigger the output bit to be read
       by the slave device. It will also cause the slave device to drive
       the input bit. Then wait the high half of the clock signal.
     */
    
    CLOCK_HIGH();
    
    DELAY_CYCLE();
    
    /* Now that the data is stable.... read it. */
    
    if (_bit_order == MSB_FIRST)
    {
      input = input << 1;
      
      temp = READ_BIT() > 0 ? 0x01 : 0x00;
      
      input |= temp;
      
    }
    else 
    {
      input = input >> 1;
      
      temp = READ_BIT() > 0 ? 0x80 : 0x00;
      
      input |= temp;
    }
    
    CLOCK_LOW();
    
  }
  
  
  return input;

}