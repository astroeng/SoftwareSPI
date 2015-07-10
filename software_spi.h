#ifndef SOFTWARE_SPI_H
#define SOFTWARE_SPI_H


#define MSB_FIRST 12
#define LSB_FIRST 13

class Software_SPI
{
public:
  Software_SPI(int input_pin,
               int output_pin,
               int clock_pin,
               int bit_order,
               int clock_uS);

  unsigned char SPI_Send_Receive(unsigned char output);
  
private:

  int _input_pin;
  int _output_pin;
  int _clock_pin;
  int _bit_order;
  int _clock_uS;

};

#endif