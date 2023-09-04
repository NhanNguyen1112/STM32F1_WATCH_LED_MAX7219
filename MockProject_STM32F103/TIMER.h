
#ifndef __Timer__
#define __Timer__

#include "STM32F1XX.h"
#include "TIMER_Register.h"

/*======================================================================================================*/
/*                              TIMER BASE                                                           */
/*======================================================================================================*/

#define PSC_TIM2_BASE (0u)
#define ARR_TIM2_BASE (72u)

extern unsigned int Tick_us;

void TIM2_Init(void);
void Delay_TIM2_ms(const unsigned int MiliSeconds);
void Delay_TIM2_us(const unsigned int MicroSeconds);
void TIM2_IRQHandler(void);
void Function_Test(void);
void Main_TIM2_BASE(void);
/*======================================================================================================*/


#endif


