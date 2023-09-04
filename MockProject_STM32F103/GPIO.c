
#include "GPIO.h"

static void SetINPUT(volatile unsigned int *GPIO_Regiter, unsigned char BitMode, unsigned char BitCNF, const unsigned char ModeInput)
{
	CLEARBIT(*GPIO_Regiter,3u,BitMode); /* Clear MODE */
	CLEARBIT(*GPIO_Regiter,3u,BitCNF); 	/* Clear CNF */

	if(ModeInput == FloatingInput) SETBIT(*GPIO_Regiter,1u,BitCNF);
	else if(ModeInput==InputPullUp_PullDown) SETBIT(*GPIO_Regiter,2u,BitCNF);
	else {}
}

static void SetPullUpDown(volatile unsigned int *GPIO_Regiter, const unsigned char Pin, const unsigned char UpDown)
{
	if(UpDown==PullUp) SETBIT(*GPIO_Regiter,1u,Pin);
	else CLEARBIT(*GPIO_Regiter,1u,Pin);
}

static void SetOUTPUT(volatile unsigned int *GPIO_Regiter, unsigned char BitMode, unsigned char BitCNF, const unsigned char ModeOutput)
{
	SETBIT(*GPIO_Regiter,3u,BitMode); /* SET MODE OUTPUT 50Mhz */
	CLEARBIT(*GPIO_Regiter,3u,BitCNF); 	/* Clear CNF */

	if(ModeOutput == OpenDrain) SETBIT(*GPIO_Regiter,1u,BitCNF);
	else if(ModeOutput==Alternate_PushPull) SETBIT(*GPIO_Regiter,2u,BitCNF);
	else if(ModeOutput==Alternate_OpenDrain) SETBIT(*GPIO_Regiter,3u,BitCNF);
	else {}
}

void SetPinInput(const unsigned char PORT, const unsigned char Pin, const unsigned char ModeInput, const unsigned char UpDown)
{
	if(Pin<=7)
	{
		unsigned char BitMode = (Pin*4);
		unsigned char BitCNF = (BitMode+2);

		if(PORT==PORTA) 
		{
			SetINPUT(&GPIO_A->GPIO_CRL,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_A->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTB) 
		{
			SetINPUT(&GPIO_B->GPIO_CRL,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_B->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTC) 
		{
			SetINPUT(&GPIO_C->GPIO_CRL,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_C->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTD) 
		{
			SetINPUT(&GPIO_D->GPIO_CRL,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_D->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTE) 
		{
			SetINPUT(&GPIO_E->GPIO_CRL,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_E->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTF) 
		{
			SetINPUT(&GPIO_F->GPIO_CRL,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_F->GPIO_ODR,Pin,UpDown);
		}
		else 
		{
			SetINPUT(&GPIO_G->GPIO_CRL,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_G->GPIO_ODR,Pin,UpDown);
		}
	}
	else 
	{
		unsigned char BitMode = ((Pin-8)*4);
		unsigned char BitCNF = (BitMode+2);

		if(PORT==PORTA) 
		{
			SetINPUT(&GPIO_A->GPIO_CRH,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_A->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTB) 
		{
			SetINPUT(&GPIO_B->GPIO_CRH,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_B->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTC) 
		{
			SetINPUT(&GPIO_C->GPIO_CRH,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_C->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTD) 
		{
			SetINPUT(&GPIO_D->GPIO_CRH,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_D->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTE) 
		{
			SetINPUT(&GPIO_E->GPIO_CRH,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_E->GPIO_ODR,Pin,UpDown);
		}
		else if(PORT==PORTF) 
		{
			SetINPUT(&GPIO_F->GPIO_CRH,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_F->GPIO_ODR,Pin,UpDown);
		}
		else 
		{
			SetINPUT(&GPIO_G->GPIO_CRH,BitMode,BitCNF,ModeInput);
			SetPullUpDown(&GPIO_G->GPIO_ODR,Pin,UpDown);
		}
	}
}

void SetPinOutput(const unsigned char PORT, const unsigned char Pin, const unsigned char ModeOutput)
{
	if(Pin<=7)
	{
		unsigned char BitMode = (Pin*4);
		unsigned char BitCNF = (BitMode+2);

		if(PORT==PORTA) SetOUTPUT(&GPIO_A->GPIO_CRL,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTB) SetOUTPUT(&GPIO_B->GPIO_CRL,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTC) SetOUTPUT(&GPIO_C->GPIO_CRL,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTD) SetOUTPUT(&GPIO_D->GPIO_CRL,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTE) SetOUTPUT(&GPIO_E->GPIO_CRL,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTF) SetOUTPUT(&GPIO_F->GPIO_CRL,BitMode,BitCNF,ModeOutput);
		else SetOUTPUT(&GPIO_G->GPIO_CRL,BitMode,BitCNF,ModeOutput);
	}
	else 
	{
		unsigned char BitMode = ((Pin-8)*4);
		unsigned char BitCNF = (BitMode+2);

		if(PORT==PORTA) SetOUTPUT(&GPIO_A->GPIO_CRH,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTB) SetOUTPUT(&GPIO_B->GPIO_CRH,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTC) SetOUTPUT(&GPIO_C->GPIO_CRH,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTD) SetOUTPUT(&GPIO_D->GPIO_CRH,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTE) SetOUTPUT(&GPIO_E->GPIO_CRH,BitMode,BitCNF,ModeOutput);
		else if(PORT==PORTF) SetOUTPUT(&GPIO_F->GPIO_CRH,BitMode,BitCNF,ModeOutput);
		else SetOUTPUT(&GPIO_G->GPIO_CRH,BitMode,BitCNF,ModeOutput);
	}
}

void WritePin(const unsigned char PORT, const unsigned char Pin, const unsigned char Status)
{
	if(Status==HIGH)
	{
		if(PORT==PORTA) SETBIT(GPIO_A->GPIO_ODR,1u,Pin);
		else if(PORT==PORTB) SETBIT(GPIO_B->GPIO_ODR,1u,Pin);
		else if(PORT==PORTC) SETBIT(GPIO_C->GPIO_ODR,1u,Pin);
		else if(PORT==PORTD) SETBIT(GPIO_D->GPIO_ODR,1u,Pin);
		else if(PORT==PORTE) SETBIT(GPIO_E->GPIO_ODR,1u,Pin);
		else if(PORT==PORTF) SETBIT(GPIO_F->GPIO_ODR,1u,Pin);
		else SETBIT(GPIO_G->GPIO_ODR,1u,Pin);
	}
	else 
	{
		if(PORT==PORTA) CLEARBIT(GPIO_A->GPIO_ODR,1u,Pin);
		else if(PORT==PORTB) CLEARBIT(GPIO_B->GPIO_ODR,1u,Pin);
		else if(PORT==PORTC) CLEARBIT(GPIO_C->GPIO_ODR,1u,Pin);
		else if(PORT==PORTD) CLEARBIT(GPIO_D->GPIO_ODR,1u,Pin);
		else if(PORT==PORTE) CLEARBIT(GPIO_E->GPIO_ODR,1u,Pin);
		else if(PORT==PORTF) CLEARBIT(GPIO_F->GPIO_ODR,1u,Pin);
		else CLEARBIT(GPIO_G->GPIO_ODR,1u,Pin);
	}
}

unsigned int ReadPin(const unsigned char PORT, const unsigned char Pin)
{
	unsigned int ReadData;
	if(PORT==PORTA) ReadData=READBIT(GPIO_A->GPIO_IDR, Pin);
	else if(PORT==PORTB) ReadData=READBIT(GPIO_B->GPIO_IDR, Pin);
	else if(PORT==PORTC) ReadData=READBIT(GPIO_C->GPIO_IDR, Pin);
	else if(PORT==PORTD) ReadData=READBIT(GPIO_D->GPIO_IDR, Pin);
	else if(PORT==PORTE) ReadData=READBIT(GPIO_E->GPIO_IDR, Pin);
	else if(PORT==PORTF) ReadData=READBIT(GPIO_F->GPIO_IDR, Pin);
	else ReadData=READBIT(GPIO_G->GPIO_IDR, Pin);
	return ReadData;
}

void TogglePin(const unsigned char PORT, const unsigned char Pin)
{
	if(PORT==PORTA) GPIO_A->GPIO_ODR ^= (1<<Pin);
	else if(PORT==PORTB) GPIO_B->GPIO_ODR ^= (1<<Pin);
	else if(PORT==PORTC) GPIO_C->GPIO_ODR ^= (1<<Pin);
	else if(PORT==PORTD) GPIO_D->GPIO_ODR ^= (1<<Pin);
	else if(PORT==PORTE) GPIO_E->GPIO_ODR ^= (1<<Pin);
	else if(PORT==PORTF) GPIO_F->GPIO_ODR ^= (1<<Pin);
	else GPIO_G->GPIO_ODR ^= (1<<Pin);
}

void Init_PA8_MCO(void)
{
	Enable_Disable_Clock_PortA(Enable); /*Enable Clock PORT A*/

	RCC->RCC_APB2ENR |= (1<<0);

	GPIO_A->GPIO_CRH &= ~(1u<<2);
	GPIO_A->GPIO_CRH |= (0xBu<<0);
}

/*==================================================================================================
*                                        FUNCTION TEST
==================================================================================================*/

/* Blink LED PC13 */
void Blink_LED(void)
{
	WritePin(PORTC,PIN13,LOW);
	Delay(1000);
	WritePin(PORTC,PIN13,HIGH);
	Delay(1000);
}

/* Button PA1 & LED PC13 */
void Button_Led(void)
{
	if(ReadPin(PORTA,PIN1))
	{
		WritePin(PORTC,PIN13,HIGH);
	}
	else 
	{
		WritePin(PORTC,PIN13,LOW);
	}
}

void Delay(unsigned int MS)
{
	unsigned int i=0, j=0;
	for(i=0 ;i<=MS;i++)
	{
		for(j=0;j<=1000;j++);
	}
}
/*==================================================================================================*/

