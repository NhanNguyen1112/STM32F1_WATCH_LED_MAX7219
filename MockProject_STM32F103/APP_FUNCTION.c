
#include "APP_FUNCTION.h"

/*===================================================================
											LOCAL VARIABLE
===================================================================*/
static DayTime_typedef Watch;
static DayTime_typedef SetTimer;

static volatile unsigned char Time_Mode;
static volatile unsigned char FlagStart;
static volatile unsigned char FlagHG;  

static unsigned char Data_Read[20];
static volatile unsigned int Length_Data_Read;

/*=================================================================*/

/*===================================================================
											LOCAL FUNCTIONS
===================================================================*/

static void LED_BUTTON_INIT(void)
{
  Enable_Disable_Clock_PortC(Enable);
  Enable_Disable_Clock_PortA(Enable);

  SetPinInput(PORTA,PIN2,InputPullUp_PullDown,PullUp);
  SetPinInput(PORTA,PIN3,InputPullUp_PullDown,PullUp);

  SetPinOutput(PORTC, PIN13, OpenDrain);
  WritePin(PORTC,PIN13,HIGH);
}

static void APP_Init(void)
{
  LED_BUTTON_INIT();

  Watch.Hour=0;
  Watch.Minute=0;
  Watch.Second=0;

  BufferClear(Data_Read,sizeof(Data_Read));

  Time_Mode = ZERO;
  Length_Data_Read=0;
  Time_Mode=0;
  FlagStart=0;
  FlagHG=0;    
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

static void Decode_Data(void)
{
  unsigned char count=0;
  unsigned char TimeData[20];

  for(count=3; count<=8; count++)
  {
    TimeData[count] = Data_Read[count]-'0';
  }

  if( (Data_Read[1]=='S') && (Data_Read[2]=='T') ) /* START */
  {
    FlagStart=START; 
  }
  else 
  {
    if ( (Data_Read[1]=='H') && (Data_Read[2]=='G') ) /* Hen gio */
    {
      FlagHG=HG;
      Link_Number(&SetTimer.Hour, &TimeData[3], &TimeData[4]);
      Link_Number(&SetTimer.Minute, &TimeData[5], &TimeData[6]);
      Link_Number(&SetTimer.Second, &TimeData[7], &TimeData[8]);
    }
    else if ( (Data_Read[1]=='A') && (Data_Read[2]=='M') ) /* AM */
    {
      Time_Mode=AM;
      Link_Number(&Watch.Hour, &TimeData[3], &TimeData[4]);
      Link_Number(&Watch.Minute, &TimeData[5], &TimeData[6]);
      Link_Number(&Watch.Second, &TimeData[7], &TimeData[8]);    
    }
    else if ( (Data_Read[1]=='P') && (Data_Read[2]=='M') ) /* PM */
    {
      Time_Mode=PM;
      Link_Number(&Watch.Hour, &TimeData[3], &TimeData[4]);
      Link_Number(&Watch.Minute, &TimeData[5], &TimeData[6]);
      Link_Number(&Watch.Second, &TimeData[7], &TimeData[8]);
    }
    else {}
  }

}

static void LED_Alarm(void)
{
  TogglePin(PORTC,PIN13);
}

static void CheckACTION(void)
{
  if( (Time_Mode==AM) || (Time_Mode==PM) )
  {
    if(FlagStart==START)
    {
      Softtimer_StartTimer(0,1000,CONTINUE,&Watch_Display);
    }
  }
}

static void CheckTIMER(void)
{
  static unsigned char Step=0;
  if(Step==0)
  {
    if( FlagHG==HG )
    {
      if( (Watch.Hour == SetTimer.Hour) &&  
          (Watch.Minute == SetTimer.Minute) &&
          (Watch.Second == SetTimer.Second))
      {
        Softtimer_StartTimer(1,1000,CONTINUE,&LED_Alarm);
        Step=1;
      }
    }
  }
  else {}
}

static void Check_Data_UART(void)
{
  static unsigned char CheckFrame=0;
  unsigned char Count=0;

  if( Length_Data_Read!=0 )
  {
    if( (Data_Read[0]=='[') && ((Data_Read[6]==']')||(Data_Read[9]==']')) )
    {
      for(Count=0; Count<Length_Data_Read; Count++)
      {
        if( ((Data_Read[Count]>=48)&&(Data_Read[Count]<=57)) ||\
            ((Data_Read[Count]>=65)&&(Data_Read[Count]<=90)) ||\
            (Data_Read[Count]=='[') || (Data_Read[Count]==']') )
        {
          CheckFrame=1;
        }
        else 
        {
          Length_Data_Read=0;
          CheckFrame=0;
          break;
        }
      }

      if(CheckFrame == 1)
      {
        Decode_Data();
        CheckACTION();
        CheckFrame=0;
        Length_Data_Read=0;
      }

    }
    else Length_Data_Read=0;      
  }

}

static void ACTION(void)
{
  Check_Data_UART();
  CheckTIMER();
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
    if( Uart_GetReceiveState()==NOT_EMP )
    {
      Length_Data_Read = Uart_GetReceiveData(Data_Read);
    }
    else 
    {
      ACTION();
    }
		
    LCD_TimeDisplay(Watch.Hour, Watch.Minute, Watch.Second);
    Softtimer_MainFunction();
    Uart_TxMainFunction();
    Delay_TIM2_ms(2);
  }

}
/*=================================================================*/


