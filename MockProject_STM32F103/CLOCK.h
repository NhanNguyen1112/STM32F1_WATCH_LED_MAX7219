
#ifndef __CLOCK__
#define __CLOCK__ 

#include "STM32F1XX.h"
#include "CLOCK_Register.h"

/*================== CONFIG CLOCK ==========================*/

/*#define FREDIV1_DIV2*/

/*#define PLLMUL_Not_X*/
/*#define PLLMUL_X4*/
/*#define PLLMUL_X5*/
/*#define PLLMUL_X6*/
/*#define PLLMUL_X7*/
/*#define PLLMUL_X8*/
#define PLLMUL_X9
/*#define PLLMUL_X6_5*/

//#define APB1_Not_Div
#define APB1_Div_2
/*#define APB1_Div_4
#define APB1_Div_8
#define APB1_Div_16*/

#define APB2_Not_Div
/*#define APB2_Div_2
#define APB2_Div_4
#define APB2_Div_8
#define APB2_Div_16*/

#define AHB_Not_Div
/*#define AHB_Div_2
#define AHB_Div_4
#define AHB_Div_8
#define AHB_Div_16
#define AHB_Div_64
#define AHB_Div_128
#define AHB_Div_256
#define AHB_Div_512*/

//#define PA8_MCO
//#define MCO_SYSCLK
//#define MCO_HSI
//#define MCO_HSE
//#define MCO_PLL_DIV2


/*===========================================================*/

void InitClockHSE(void);

void Enable_Disable_Clock_PortA(const unsigned char Status);
void Enable_Disable_Clock_PortB(const unsigned char Status);
void Enable_Disable_Clock_PortC(const unsigned char Status);
void Enable_Disable_Clock_PortD(const unsigned char Status);
void Enable_Disable_Clock_PortE(const unsigned char Status);
void Enable_Disable_Clock_PortF(const unsigned char Status);
void Enable_Disable_Clock_PortG(const unsigned char Status);
void Clock_AFIO(const unsigned char Status);
void Clock_SPI1(const unsigned char Status);
void I2C1_EnableClock(const unsigned char Status);
void I2C2_EnableClock(const unsigned char Status);
void DMA1_EnableClock(const unsigned char Status);
void DMA2_EnableClock(const unsigned char Status);
void ADC_EnableClock(const unsigned char ADC, const unsigned char Status, const unsigned char DIV);

#endif



