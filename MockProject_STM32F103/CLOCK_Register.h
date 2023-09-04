
#ifndef _Clock_Register_
#define _Clock_Register_

#include "CLOCK.h"

typedef struct
{
	volatile unsigned int RCC_CR;
	volatile unsigned int RCC_CFGR;
	volatile unsigned int RCC_CIR;
	volatile unsigned int RCC_APB2RSTR;
	volatile unsigned int RCC_APB1RSTR;
	volatile unsigned int RCC_AHBENR;
	volatile unsigned int RCC_APB2ENR;
	volatile unsigned int RCC_APB1ENR;
	volatile unsigned int RCC_BDCR;
	volatile unsigned int RCC_CSR;
	volatile unsigned int RCC_AHBRSTR;
	volatile unsigned int RCC_CFGR2;
}rcc_typedef;

#define RCC_BASE_ADDRESS 		((unsigned int)0x40021000u)
#define RCC 		            ((rcc_typedef*)RCC_BASE_ADDRESS)

#endif


