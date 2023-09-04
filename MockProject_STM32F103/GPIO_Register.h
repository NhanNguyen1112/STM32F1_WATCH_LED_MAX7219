
#ifndef _Gpio_Register_
#define _Gpio_Register_ 

#include "GPIO.h"

typedef struct 
{
	volatile unsigned int GPIO_CRL;
	volatile unsigned int GPIO_CRH;
	volatile unsigned int GPIO_IDR;
	volatile unsigned int GPIO_ODR;
	volatile unsigned int GPIO_BSRR;
	volatile unsigned int GPIO_BRR;
	volatile unsigned int GPIO_LCKR;
}GPIO_typedef;

typedef struct
{
	volatile unsigned int AFIO_EVCR;
	volatile unsigned int AFIO_MAPR;
	volatile unsigned int AFIO_EXTICR1;
	volatile unsigned int AFIO_EXTICR2;
	volatile unsigned int AFIO_EXTICR3;
	volatile unsigned int AFIO_EXTICR4;
	volatile unsigned int AFIO_MAPR2;
}AFIO_typedef;

#define GPIOA_BASE_ADDRESS 			((unsigned int)0x40010800u)
#define GPIOB_BASE_ADDRESS 			((unsigned int)0x40010C00u)
#define GPIOC_BASE_ADDRESS 			((unsigned int)0x40011000u)
#define GPIOD_BASE_ADDRESS 			((unsigned int)0x40011400u)
#define GPIOE_BASE_ADDRESS 			((unsigned int)0x40011800u)
#define GPIOF_BASE_ADDRESS 			((unsigned int)0x40011C00u)
#define GPIOG_BASE_ADDRESS 			((unsigned int)0x40012000u)
#define AFIO_BASE_ADDRESS 			((unsigned int)0x40010000u)

#define GPIO_A 	((GPIO_typedef*)GPIOA_BASE_ADDRESS)
#define GPIO_B 	((GPIO_typedef*)GPIOB_BASE_ADDRESS)
#define GPIO_C 	((GPIO_typedef*)GPIOC_BASE_ADDRESS)
#define GPIO_D 	((GPIO_typedef*)GPIOD_BASE_ADDRESS)
#define GPIO_E 	((GPIO_typedef*)GPIOE_BASE_ADDRESS)
#define GPIO_F 	((GPIO_typedef*)GPIOF_BASE_ADDRESS)
#define GPIO_G 	((GPIO_typedef*)GPIOG_BASE_ADDRESS)
#define AFIO 		((AFIO_typedef*)AFIO_BASE_ADDRESS)

#endif


