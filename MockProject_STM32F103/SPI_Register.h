
#ifndef _SPI_Register_
#define _SPI_Register_ 

#include "SPI.h"

typedef struct
{
  volatile unsigned int CR1;
  volatile unsigned int CR2;
  volatile unsigned int SR;
  volatile unsigned int DR;
  volatile unsigned int CRCPR;
  volatile unsigned int RXCRCR;
  volatile unsigned int TXCRCR;
  volatile unsigned int I2SCFGR;
  volatile unsigned int I2SPR;
}SPI_typedef;

#define SPI1_BASE_ADDRESS 			((unsigned int)0x40013000u)
#define SPI2_I2S_BASE_ADDRESS 	((unsigned int)0x40003800u)
#define SPI3_I2S_BASE_ADDRESS 	((unsigned int)0x40003C00u)

#define SPI1      ((SPI_typedef *) SPI1_BASE_ADDRESS)
#define SPI2_I2S  ((SPI_typedef *) SPI2_I2S_BASE_ADDRESS)
#define SPI3_I2S  ((SPI_typedef *) SPI3_I2S_BASE_ADDRESS)

#endif


