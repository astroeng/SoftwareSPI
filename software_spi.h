#ifndef SOFTWARE_SPI_H
#define SOFTWARE_SPI_H


#define MSB_FIRST 12
#define LSB_FIRST 13

/* This class will, given the correct pins, handle the transactions on an 
   SPI bus. This class does not use the chip select pin and that should be
   handled by outside code. Doing so allows a single SPI class to interface
   with many SPI devices.
 
   The SPI_Send_Receive function input will be written to the SPI bus. At 
   the same time the function will read the input pin and return the resultant
   byte as the return parameter. This enables the most efficient use of the 
   bus as data can move in both directions at the same time. If a device does
   not support such a transaction then 0x00 may be written to the SPI bus
   during read operations.
 */

class Software_SPI
{
public:
  Software_SPI(int input_pin,
               int output_pin,
               int clock_pin,
               int bit_order,
               int clock_uS);

  unsigned char SPI_Send_Receive(unsigned char output);
  void reset();
  
private:

  int _input_pin;
  int _output_pin;
  int _clock_pin;
  int _bit_order;
  int _clock_uS;

};

#endif