
#include "UART.h"

static unsigned char Transmit_State=0;
static unsigned char Receive_State=0;

static unsigned char Software_Buffer_Send[UART_BUFFER_SIZE];
static unsigned char Software_Buffer_Read[UART_BUFFER_SIZE];

static unsigned int LengthBufferSend=0;
static unsigned int LengthBufferRead=0;
static unsigned char Index_Read=0;
static unsigned char Index_Write=0;

static void Setup_GPIO_PA9TX_PA10RX(void)
{
  Enable_Disable_Clock_PortA(Enable);

  /* PA9 TX -> OUTPUT, CNF: ALT Push-pull */
  SetPinOutput(PORTA,PIN9,Alternate_PushPull);

  /* PA10 RX -> INPUT, Pull-up */
  SetPinInput(PORTA,PIN10,InputPullUp_PullDown,PullUp);

  AFIO->AFIO_MAPR &= ~(1u<<2); /* USART1 no remap */

}

static void USART1_Init_CLK(void)
{
  RCC->RCC_APB2ENR |= (1u<<14); /* enable clock USART 1 */
}

/* PA9-TX ; PA10-RX ; Baudrate:9600 */
void USART1_Init(void)
{
  Setup_GPIO_PA9TX_PA10RX();
  USART1_Init_CLK();

  USART1->CR1 |= (1u<<3);   /* enable Transmitter */
  USART1->CR1 |= (1u<<2);   /* enable Receiver */
  USART1->CR1 &= ~(1u<<12); /* M: 1 start bit, 8 data, 1 stop bit */
  USART1->CR1 |= (1u<<5);   /* RXNEIE: RX interrupt enable */

  /* APB2 CLK= 72Mhz */
  /* Baudrate= 9600 */
  /* OVER8=0 -> sample 16 */
  /* 72.000.000/(16*9600) = 468.75 */
  /* DIV_Mantissa = 468 */
  /* DIV_Fraction = 16*0.75 = 12 */
  USART1->BRR |= (0x1D4u<<4); /* Set  DIV_Mantissa */
  USART1->BRR |= (0xCu<<0);   /* Set  DIV_Fraction */

  USART1->CR1 |= (1u<<13); /* Enable USART1 */

  NVIC_SetPriority(USART1_IRQn,0);    /* Set priority */
  NVIC_ClearPendingFlag(USART1_IRQn); /* interrupt clear pending USART1 */
  NVIC_EnableInterrupt(USART1_IRQn);  /* enable interrupt USART1 */

  Transmit_State=IDLE;
	Receive_State=EMPTY;

}

void USART1_IRQHandler(void)
{
  Uart_RxMainFunction();
}

unsigned char Uart_Transmit ( unsigned char* u8_TxBuffer, unsigned int u4_Length )
{
  unsigned int Count=0;
	unsigned char State=ACCEPT;

	if(Transmit_State == IDLE)
	{
		for(Count=0; Count<u4_Length; Count++)
		{
			Software_Buffer_Send[Count] = *u8_TxBuffer;
			u8_TxBuffer++;
			LengthBufferSend++;
		}
		Transmit_State=BUSY;
	}
	else State=NOT_ACCEPT;

	return State;
}

unsigned char Uart_GetTransmitState ( void )
{
	return Transmit_State;
}

void Uart_TxMainFunction ( void )
{
	static unsigned int idex=0;
	if(Transmit_State == BUSY)
	{
		if( (USART1->SR & (1u<<7)) && (LengthBufferSend!=0) )
		{
			USART1->DR = (unsigned int)Software_Buffer_Send[idex];
			idex++;
			LengthBufferSend--;
		}
		else 
		{
			idex=0; 
			Transmit_State=IDLE;
		}
	}
}

unsigned int Uart_GetReceiveData ( unsigned char * u8_RxBuffer )
{
	static unsigned int LengthCount=0;

	if(Receive_State == NOT_EMP)
	{
		if(Index_Read != Index_Write)
		{
			u8_RxBuffer[LengthCount] = Software_Buffer_Read[Index_Read];
			LengthCount++;

			if( Index_Read>=(UART_BUFFER_SIZE-1) ) Index_Read=0;
			else Index_Read++;					
		}
		else 
		{
			LengthBufferRead = LengthCount;
			Receive_State = EMPTY;
		}
	}
	else LengthCount=0;

	return LengthBufferRead;
}

unsigned char Uart_GetReceiveState ( void )
{
	return Receive_State;
}

void Uart_RxMainFunction ( void )
{
	Software_Buffer_Read[Index_Write] = (unsigned char)(USART1->DR);
	
	if( Index_Write>=(UART_BUFFER_SIZE-1) ) Index_Write=0;
	else Index_Write++;

  Receive_State = NOT_EMP;
}

/*=============================================================================
							MAIN UART TEST
=============================================================================*/

static unsigned char TestDataSend[5]= {'A','B','C','D','-'};
static unsigned char TestReadData[20];
unsigned int CheckRead=0;

void UART_V2_MAIN_TEST(void)
{
  InitClockHSE();
  TIM2_Init();
	USART1_Init();

  Enable_Disable_Clock_PortB(Enable);
  SetPinInput(PORTB,PIN6,InputPullUp_PullDown,PullUp);
  SetPinInput(PORTB,PIN7,InputPullUp_PullDown,PullUp);
	
	while(1)
	{
    if( ReadPin(PORTB,PIN6) == 0 )
    {
      Uart_Transmit(TestDataSend,sizeof(TestDataSend));
    }

		// if( Uart_GetReceiveState() == EMPTY )
		// {
		// 	Uart_GetReceiveData(TestReadData);
		// }

    //if( ReadPin(PORTB,PIN7) == 0 )
		//{
			Uart_GetReceiveData(TestReadData);
		//}	
		
		Uart_TxMainFunction();
		
		Delay_TIM2_ms(2);
		
	}
}

/*=============================================================================*/

