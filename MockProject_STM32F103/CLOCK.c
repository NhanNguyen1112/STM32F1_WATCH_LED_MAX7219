
#include "CLOCK.h"

void InitClockHSE(void)
{
	RCC->RCC_CFGR &= ~(3u<<0);    /* SW Select HSI */

  RCC->RCC_AHBENR &= ~(1u<<12); /* OTGFSEN Disable */
	RCC->RCC_CR &= ~(1u<<24);     /* Disable PLL */
	
	RCC->RCC_CR |= (1<<16);                 /* Enable HSE 8Mhz */
  while( (RCC->RCC_CR & (1<<17)) == 0 );  /* Wait HSERD */
  
  RCC->RCC_CFGR2 &= ~(1u<<16u); /* FREDIV1SRC Set HSE clock */

  RCC->RCC_CFGR2 &= ~(0xFu<<0); /* FREDIV1 not divided = 8Mhz*/
  #ifdef FREDIV1_DIV2
  RCC->RCC_CFGR2 |= (1u<<0);    /* FREDIV1 /2 */
  #endif

  RCC->RCC_CFGR  |= (1<<16);    /* PLLSRC set FREDIV1 */
  
  /* Set PLLMUL */
  RCC->RCC_CFGR  &= ~(0xFu<<18);  /* PLLMUL set not divided */
  #ifdef PLLMUL_X4
  RCC->RCC_CFGR  |= (2u<<18);   /* PLLMUL X4 */
  #endif
  #ifdef PLLMUL_X5
  RCC->RCC_CFGR  |= (3u<<18);   /* PLLMUL X5 */
  #endif
  #ifdef PLLMUL_X6
  RCC->RCC_CFGR  |= (4u<<18);   /* PLLMUL X6 */
  #endif
  #ifdef PLLMUL_X7
  RCC->RCC_CFGR  |= (5u<<18);   /* PLLMUL X7 */
  #endif
  #ifdef PLLMUL_X8
  RCC->RCC_CFGR  |= (6u<<18);   /* PLLMUL X8 */
  #endif
  #ifdef PLLMUL_X9
	RCC->RCC_CFGR  |= (7u<<18);     /* PLLMUL X9 */
  #endif
  #ifdef PLLMUL_X6_5
  RCC->RCC_CFGR  |= (13u<<18);   /* PLLMUL X6.5 */
  #endif
  
  /* Set APB1 */
  RCC->RCC_CFGR &= ~(1u<<10u);  /* PPRE2 APB1 not divided */
  #ifdef APB1_Div_2
  RCC->RCC_CFGR |= (4u<<10u);   /* PPRE2 APB1 /2 */
  #endif
  #ifdef APB1_Div_4
  RCC->RCC_CFGR |= (5u<<10u);   /* PPRE2 APB1 /4 */
  #endif
  #ifdef APB1_Div_8
  RCC->RCC_CFGR |= (6u<<10u);   /* PPRE2 APB1 /8 */
  #endif
  #ifdef APB1_Div_16
  RCC->RCC_CFGR |= (7u<<10u);   /* PPRE2 APB1 /16 */
  #endif

  /* Set APB2 */
  RCC->RCC_CFGR &= ~(1u<<13u);  /* PPRE2 APB2 not divided */
  #ifdef APB2_Div_2
  RCC->RCC_CFGR |= (4u<<13u);   /* PPRE2 APB2 /2 */
  #endif
  #ifdef APB2_Div_4
  RCC->RCC_CFGR |= (5u<<13u);   /* PPRE2 APB2 /4 */
  #endif
  #ifdef APB2_Div_8
  RCC->RCC_CFGR |= (6u<<13u);   /* PPRE2 APB2 /8 */
  #endif
  #ifdef APB2_Div_16
  RCC->RCC_CFGR |= (7u<<13u);   /* PPRE2 APB2 /16 */
  #endif

  /* Set AHB */
  RCC->RCC_CFGR &= ~(0xFu<<4u); /* HPRE AHB prescaler not divided */
  #ifdef AHB_Div_2
  RCC->RCC_CFGR |= (8u<<4u); /* HPRE AHB /2 */
  #endif
  #ifdef AHB_Div_4
  RCC->RCC_CFGR |= (9u<<4u); /* HPRE AHB /4 */
  #endif
  #ifdef AHB_Div_8
  RCC->RCC_CFGR |= (10u<<4u); /* HPRE AHB /8 */
  #endif
  #ifdef AHB_Div_16
  RCC->RCC_CFGR |= (11u<<4u); /* HPRE AHB /16 */
  #endif
  #ifdef AHB_Div_64
  RCC->RCC_CFGR |= (12u<<4u); /* HPRE AHB /64 */
  #endif
  #ifdef AHB_Div_128
  RCC->RCC_CFGR |= (13u<<4u); /* HPRE AHB /128 */
  #endif
  #ifdef AHB_Div_256
  RCC->RCC_CFGR |= (14u<<4u); /* HPRE AHB /256 */
  #endif
  #ifdef AHB_Div_512
  RCC->RCC_CFGR |= (15u<<4u); /* HPRE AHB /512 */
  #endif
	
	RCC->RCC_CFGR |= (1u<<0);   /* SW Select HSE */
  RCC->RCC_CR &= ~(1u << 0);  /* Disable HSI */
  
  RCC->RCC_CR |= (1u<<24);    /* Enable PLL */

  RCC->RCC_CFGR &= ~(0xFu<<24u);  /* MCO ALL clear */
  #ifdef MCO_SYSCLK
  RCC->RCC_CFGR |= (4u<<24u);     /* MCO Check SYSCLK */
  #endif
  #ifdef MCO_HSI
  RCC->RCC_CFGR |= (5u<<24u);   /* MCO Check HSI */
  #endif
  #ifdef MCO_HSE
  RCC->RCC_CFGR |= (6u<<24u);   /* MCO Check HSE */
  #endif
  #ifdef MCO_PLL_DIV2
  RCC->RCC_CFGR |= (7u<<24u);   /* MCO Check PLL/2 */
  #endif

  RCC->RCC_CFGR &= ~(1u<<0);  /* SW Clear */
	RCC->RCC_CFGR |= (2u<<0);   /* SW Select PLLCLK */

  while (!(RCC->RCC_CFGR & (1u << 3)));

  #ifdef PA8_MCO
  Init_PA8_MCO(); /* PA8 output clock */
  #endif

}

void Enable_Disable_Clock_PortA(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,2);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,2);
}

void Enable_Disable_Clock_PortB(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,3);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,3);
}

void Enable_Disable_Clock_PortC(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,4);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,4);
}

void Enable_Disable_Clock_PortD(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,5);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,5);
}

void Enable_Disable_Clock_PortE(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,6);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,6);
}

void Enable_Disable_Clock_PortF(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,7);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,7);
}

void Enable_Disable_Clock_PortG(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,8);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,8);
}

void Clock_AFIO(const unsigned char Status)
{
  if(Status==Enable) RCC->RCC_APB2ENR |= (1<<0);
  else RCC->RCC_APB2ENR &= ~(1u<<0);
}

void Clock_SPI1(const unsigned char Status)
{
  if(Status==Enable) RCC->RCC_APB2ENR |= (1<<12);
  else RCC->RCC_APB2ENR &= ~(1u<<12);
}

void I2C1_EnableClock(const unsigned char Status)
{
  if(Status==Enable) RCC->RCC_APB1ENR |= (1u<<21);
  else RCC->RCC_APB1ENR &= ~(1u<<21);
}

void I2C2_EnableClock(const unsigned char Status)
{
  if(Status==Enable) RCC->RCC_APB1ENR |= (1u<<22);
  else RCC->RCC_APB1ENR &= ~(1u<<22);
}

void DMA1_EnableClock(const unsigned char Status)
{
  if(Status==Enable) RCC->RCC_AHBENR |= (1u<<0);
  else RCC->RCC_AHBENR &= ~(1u<<0);
}

void DMA2_EnableClock(const unsigned char Status)
{
  if(Status==Enable) RCC->RCC_AHBENR |= (1u<<1);
  else RCC->RCC_AHBENR &= ~(1u<<1);
}

/*  
  DIV 2,4,6,8 
  ADC: 1-ADC1 , 2-ADC2 , 0-ADC1 & ADC2
*/
void ADC_EnableClock(const unsigned char ADC, const unsigned char Status, const unsigned char DIV)
{
  RCC->RCC_CFGR &= ~(3u<<14);
  if(DIV==4) RCC->RCC_CFGR |= (1u<<14);
  else if (DIV==6) RCC->RCC_CFGR |= (2u<<14);
  else if (DIV==8) RCC->RCC_CFGR |= (3u<<14);
  else {}

  if(ADC==1)
  {
    if(Status==Enable) RCC->RCC_APB2ENR |= (1u<<9);
    else RCC->RCC_APB2ENR &= ~(1u<<9);
  }
  else if(ADC==2)
  {
    if(Status==Enable) RCC->RCC_APB2ENR |= (1u<<10);
    else RCC->RCC_APB2ENR &= ~(1u<<10);
  }
  else 
  {
    if(Status==Enable)
    {
      RCC->RCC_APB2ENR |= (1u<<9);
      RCC->RCC_APB2ENR |= (1u<<10);
    } 
    else
    {
      RCC->RCC_APB2ENR &= ~(1u<<9);
      RCC->RCC_APB2ENR &= ~(1u<<10);
    } 
  }

}


