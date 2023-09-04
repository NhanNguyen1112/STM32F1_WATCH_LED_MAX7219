#ifndef _NVIC_Register_
#define _NVIC_Register_

#include "NVIC.h"

typedef struct 
{
  volatile unsigned int ISER[8u];        
	unsigned int RESERVED_0[24];
  volatile unsigned int ICER[8u];       
  unsigned int RESERVED_1[24];
  volatile unsigned int ISPR[8u];       
  unsigned int RESERVED_2[24];
  volatile unsigned int ICPR[8u];       
  unsigned int RESERVED_3[24];
  volatile unsigned int IABR[8u];       
  unsigned char RESERVED_4[224u];
  volatile unsigned int IPR[60u];      
  unsigned char RESERVED_5[2573u];
  volatile unsigned int STIR;          
} NVIC_Typedef;

#define NVIC_BASE_ADDRESS   ((unsigned int)0xE000E100u)
#define NVIC 				        ((NVIC_Typedef*)NVIC_BASE_ADDRESS)

#endif

