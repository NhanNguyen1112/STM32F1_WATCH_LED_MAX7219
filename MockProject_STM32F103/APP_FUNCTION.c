
#include "APP_FUNCTION.h"

/*===================================================================
											LOCAL VARIABLE
===================================================================*/
static DayTime_typedef Watch;
static DayTime_typedef SetTimer;
static unsigned char Time_Mode=0;
static unsigned char Action_Mode=0;
static unsigned char Data_Read[20];
static unsigned char Action_Buffer[20];
static unsigned int Length_Data_Read=0;
static unsigned char Step_Action=0;
/*=================================================================*/

/*===================================================================
											LOCAL FUNCTIONS
===================================================================*/
static void APP_Init(void)
{
  Watch.Hour=0;
  Watch.Minute=0;
  Watch.Second=0;

  Time_Mode = AM;
}

static void Watch_Display(void)
{
  if(Watch.Second >= 59) 
  {
    Watch.Second=0;
    if(Watch.Minute >= 59) 
    {
			Watch.Minute=0;
      if(Time_Mode == AM) /* AM */
      {
        if( Watch.Hour>=12 ) Watch.Hour=1;
        else Watch.Hour++;
      }
      else /* PM */ 
      {
        if( Watch.Hour>=23 ) Watch.Hour=0;
        else Watch.Hour++;
      }

    }
    else Watch.Minute++;
    
  }
  else Watch.Second++;
  
}

static void Link_Number(unsigned char *Des, unsigned char *a, unsigned char *b)
{
	*Des = ( ((*a) * 10) + (*b) );
}

static void F_SaveTime(DayTime_typedef TimeSave)
{
  Watch=TimeSave;
}

static void F_SetTimer(DayTime_typedef TimerSet)
{
  SetTimer=TimerSet;
}

static void Decode_Data(unsigned char *Data)
{
  unsigned char TimeData[20];

  TimeData[3] = Data[3]-'0';
  TimeData[4] = Data[4]-'0';
  TimeData[5] = Data[5]-'0';
  TimeData[6] = Data[6]-'0';
  TimeData[7] = Data[7]-'0';
  TimeData[8] = Data[8]-'0';

  if( strcmp(Data,"[START]")==1 ) /* START */
  {
    Action_Mode=START;
  }
  else 
  {
    if( (Data[1]=='H') && (Data[2]=='G') ) /* Hen gio */
    {
      Action_Mode=HG;
      Link_Number(&SetTimer.Hour, &TimeData[3], &TimeData[4]);
      Link_Number(&SetTimer.Minute, &TimeData[5], &TimeData[6]);
      Link_Number(&SetTimer.Second, &TimeData[7], &TimeData[8]);
    }
    else 
    {
      if( (Data[1]=='A') && (Data[2]=='M') ) /* AM */
      {
        Time_Mode=AM;
      }
      else /* PM */
      {
        Time_Mode=PM;
      }
      Link_Number(&Watch.Hour, &TimeData[3], &TimeData[4]);
      Link_Number(&Watch.Minute, &TimeData[5], &TimeData[6]);
      Link_Number(&Watch.Second, &TimeData[7], &TimeData[8]);
    }

    BufferClear(Data_Read,Length_Data_Read);
    Length_Data_Read=0;
    Step_Action=0;
  }

}

static void Check_Data_UART(void)
{
  unsigned char Count=0;

  if(Length_Data_Read != 0)
  {
    if( (Data_Read[0]=='[') && ((Data_Read[6]==']')||(Data_Read[9]==']')) ) 
    {
      for(Count=0; Count<Length_Data_Read; Count++)
      {
        if( ((Data_Read[Count]>=48)&&(Data_Read[Count]<=57)) ||\
            ((Data_Read[Count]>=65)&&(Data_Read[Count]<=90)) ||\
            (Data_Read[Count]=='[') || (Data_Read[Count]==']') )
        {
          Action_Buffer[Count] = Data_Read[Count];
          Step_Action=1;
        }
        else 
        {
					Length_Data_Read=0;
          BufferClear(Data_Read,Length_Data_Read);
          
          break;
        }
        
      }

    } 
    else 
    {
			Length_Data_Read=0;
      BufferClear(Data_Read,Length_Data_Read);
    } 
  }
}

static void Check_Action_Mode(void)
{

}

static void ACTION(void)
{
  if(Step_Action==0) /* Read Data */
  {
    Check_Data_UART();
  }
  else /* Decode Data */
  {
    Decode_Data(Action_Buffer);
  }
}

/*=================================================================*/

/*===================================================================
											GLOBAL FUNCTIONS
===================================================================*/
void MAIN_APP(void)
{
  InitClockHSE();
  Softtimer_Init();
  USART1_Init();
  SPI1_Init();
  TIM2_Init();
  MAX7219_Init();

  APP_Init();

  while(1)
  {
		ACTION();
		
    LCD_TimeDisplay(Watch.Hour, Watch.Minute, Watch.Second);

    Length_Data_Read = Uart_GetReceiveData(Data_Read);
    Softtimer_MainFunction();
    Uart_TxMainFunction();
    Delay_TIM2_ms(2);
  }

}
/*=================================================================*/


