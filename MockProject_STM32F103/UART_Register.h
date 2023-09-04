#ifndef _USART_Register_
#define _USART_Register_

#include "UART.h"

typedef struct
{
  volatile unsigned int SR;
  volatile unsigned int DR;
  volatile unsigned int BRR;
  volatile unsigned int CR1;
  volatile unsigned int CR2;
  volatile unsigned int CR3;
  volatile unsigned int GTPR;
}Usart_typedef;

#define USART1_BASE_ADDRESS 		((unsigned int)0x40013800u)
#define USART2_BASE_ADDRESS 		((unsigned int)0x40004400u)
#define USART3_BASE_ADDRESS 		((unsigned int)0x40004800u)
#define UART4_BASE_ADDRESS 			((unsigned int)0x40004C00u)
#define UART5_BASE_ADDRESS 			((unsigned int)0x40005000u)

#define USART1  ((Usart_typedef *)USART1_BASE_ADDRESS)
#define USART2  ((Usart_typedef *)USART2_BASE_ADDRESS)
#define USART3  ((Usart_typedef *)USART3_BASE_ADDRESS)
#define UART4   ((Usart_typedef *)UART4_BASE_ADDRESS)
#define UART5   ((Usart_typedef *)UART5_BASE_ADDRESS)

#endif /* _USART_Register_ */

