
#include "TIMER.h"

/*======================================================================================================*/
/*                              TIMER BASE                                                           */
/*======================================================================================================*/
static unsigned int Count=0;
unsigned int Tick_us=0;

void TIM2_Init(void)
{
  unsigned int CR1=0;

  RCC->RCC_APB1ENR |= (1u<<0); /* Enable clock TIM2 */

  TIM2->PSC = PSC_TIM2_BASE; /* Prescaler = (0-1)+1 = 0 -> 72mhz/0 = 72mhz */

  /* SYSCLK=72Mhz -> ARR=1us -> 72.000.000*0,000001= 72 tick */
  TIM2->ARR = ARR_TIM2_BASE;

  TIM2->CNT = 0; /* Reset counter */

  TIM2->DIER |= (1<<0);  /* UIE: Update interrupt enable */
  TIM2->SR &= ~(1u<<0);  /* UIF: Clear UIF update interrupt flag */

  NVIC_ClearPendingFlag(TIM2_IRQn); /* Clear Pending */
  NVIC_SetPriority(SPI1_IRQn,1);
  NVIC_EnableInterrupt(TIM2_IRQn); 	/* Enable interupt */

  CR1 &= ~(1u<<4); 	/* DIR set Up counter */
  CR1 |= (1u<<0); 	/* enable counter */
  TIM2->CR1 = CR1;  

  TIM2->EGR = 0x01u; /* UG Re-initialize the counter and generates an update of the registers */
}

void Delay_TIM2_ms(const unsigned int MiliSeconds)
{
  unsigned int MicroSeconds = MiliSeconds*1000;
  while(Count<=MicroSeconds);
  Count=0;
}

void Delay_TIM2_us(const unsigned int MicroSeconds)
{
  while(Count<=(MicroSeconds-1));
  Count=0;
}

void TIM2_IRQHandler(void)
{
  TIM2->SR &= ~(1u<<0);  /* UIF: Clear UIF update interrupt flag */
	Count+=1;
  Tick_us+=1;
}
/*======================================================================================================*/



