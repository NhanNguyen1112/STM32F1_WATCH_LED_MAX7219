#ifndef _Systick_Register_
#define _Systick_Register_

#include "Softtimer.h"

typedef struct
{
	volatile unsigned int SYST_CSR;
	volatile unsigned int SYST_RVR;
	volatile unsigned int SYST_CVR;
	volatile unsigned int SYST_CALIB;
}Systick_typedef;

#define SYSTICK_BASE_ADDRESS  ((unsigned int)0xE000E010u)
#define SYSTICK 		          ((Systick_typedef*)SYSTICK_BASE_ADDRESS)

#endif /* _Systick_Register_ */



