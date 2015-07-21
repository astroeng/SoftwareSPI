Software SPI
============

There are several different software SPI libraries out there. This one is my take on the age old art of bit-banging. A couple of the libraries that were considered before writing this did not seem to have the capability to read and write the bus concurrently. Bit-banging is certainly not the most efficient thing but, being able to read and write the bus concurrently makes this implementation more efficient.

Use
---

`#define SPI_DATA_IN 7
#define SPI_DATA_OUT 8
#define SPI_CLOCK    9
#define BIT_ORDER    MSB_FIRST  // or LSB_FIRST
#define CLOCK_DELAY  500        // in microSeconds
Software_SPI spi_bus(SPI_DATA_IN, SPI_DATA_OUT, SPI_CLOCK, BIT_ORDER, CLOCK_DELAY);`

`int data_out = 0x11;
int data_in = SPI_Send_Receive(data_out);`
  