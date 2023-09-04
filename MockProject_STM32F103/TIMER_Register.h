
#ifndef __Timer_Register__
#define __Timer_Register__

#include "TIMER.h"

typedef struct
{
  volatile unsigned int CR1;
  volatile unsigned int CR2;
  volatile unsigned int SMCR;
  volatile unsigned int DIER;
  volatile unsigned int SR;
  volatile unsigned int EGR;
  volatile unsigned int CCMR1;
  volatile unsigned int CCMR2;
  volatile unsigned int CCER;
  volatile unsigned int CNT;
  volatile unsigned int PSC;
  volatile unsigned int ARR;
  char dummy[4];
  volatile unsigned int CCR1;
  volatile unsigned int CRR2;
  volatile unsigned int CCR3;
  volatile unsigned int CCR4;
  char dummy1[4];
  volatile unsigned int DCR;
  volatile unsigned int DMAR;
}TIM2to5_typedef;

#define TIM1_BASE_ADDRESS 			((uint32_t)0x40022C00u)
#define TIM2_BASE_ADDRESS 			((uint32_t)0x40000000u)
#define TIM3_BASE_ADDRESS 			((uint32_t)0x40000400u)
#define TIM4_BASE_ADDRESS 			((uint32_t)0x40000800u)
#define TIM5_BASE_ADDRESS 			((uint32_t)0x40000C00u)
#define TIM6_BASE_ADDRESS 			((uint32_t)0x40001000u)
#define TIM7_BASE_ADDRESS 			((uint32_t)0x40001400u)
#define TIM8_BASE_ADDRESS 			((uint32_t)0x40013400u)
#define TIM9_BASE_ADDRESS 			((uint32_t)0x40014C00u)
#define TIM10_BASE_ADDRESS 			((uint32_t)0x40015000u)
#define TIM11_BASE_ADDRESS 			((uint32_t)0x40015400u)
#define TIM12_BASE_ADDRESS 			((uint32_t)0x40001800u)
#define TIM13_BASE_ADDRESS 			((uint32_t)0x40001C00u)
#define TIM14_BASE_ADDRESS 			((uint32_t)0x40002000u)

#define TIM2 ((TIM2to5_typedef *)TIM2_BASE_ADDRESS)
#define TIM3 ((TIM2to5_typedef *)TIM3_BASE_ADDRESS)
#define TIM4 ((TIM2to5_typedef *)TIM4_BASE_ADDRESS)
#define TIM5 ((TIM2to5_typedef *)TIM5_BASE_ADDRESS)

#endif



