
#ifndef _SPI_H
#define _SPI_H

#include "STM32F1XX.h"
#include "SPI_Register.h"

/*
 * SPI1
 * NSS : PA4 (General purpose output push-pull)
 * SCK : PA5 (Alternate function push-pull)
 * MISO: PA6 (Input floating / Input pull-up)
 * MOSI: PA7 (Alternate function push-pull)
 */

#define Master_Config
// #define Slave_Config

//#define Baudrate_Div2              /* Fpclk/2 */
//#define Baudrate         ((1u<<3)) /* Fpclk/4 */
// #define Baudrate         ((2u<<3)) /* Fpclk/8 */
// #define Baudrate         ((3u<<3)) /* Fpclk/16 */
// #define Baudrate         ((4u<<3)) /* Fpclk/32 */
// #define Baudrate         ((5u<<3)) /* Fpclk/64 */
#define Baudrate         ((6u<<3)) /* Fpclk/128 */
// #define Baudrate         ((7u<<3)) /* Fpclk/256 */

#define SPI1_16_BIT_FORMAT
// #define SPI1_8_BIT_FORMAT

#define SOFT_SLAVE_ENABLE
// #define SOFT_SLAVE_DISABLE

#define Full_Duplex
// #define Recieve_Only

/*===================================================================*/

void SPI_MAINTEST(void);

void SPI1_Init(void);
void SPI1_Enable(void);
void SPI1_Disable(void);
void SPI1_EnableSlave(void);
void SPI1_DisableSlave(void);
void SPI1_IRQHandler(void);

void SPI1_Send16bit(unsigned short *DataSend);
void SPI1_SendData(unsigned char *DataSend, const unsigned int Len);
void SPI1_ReadData(unsigned char *DataSend, const unsigned int Len);

#endif


