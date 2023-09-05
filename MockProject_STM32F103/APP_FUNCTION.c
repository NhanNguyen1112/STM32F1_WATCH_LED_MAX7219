
#include "APP_FUNCTION.h"

#define TickMicroSecond (1000u)
#define Softtimer_START (0u)
#define Softtimer_Alarm (1u)

/*===================================================================
											TYPEDEFS & ENUM
===================================================================*/
typedef struct DayTime_typedef
{
  unsigned char Hour;
  unsigned char Minute;
  unsigned char Second;
  unsigned char Day;
  unsigned char Month;
  unsigned char Year;
}DayTime_typedef;

typedef enum TimeMode_enum
{
  ZERO,
  AM,
  PM,
  HG,
  START
}TimeMode_enum;

typedef enum TRUE_FALSE
{
  FALSE,
  TRUE
}TrueFalse_enum;

typedef enum MenuSelect
{
  No_Menu_Select,
  Menu_ConfigTime,
  Menu_TimerAlarm,
  SelectPos
}Menu_enum;
/*=================================================================*/

/*===================================================================
											LOCAL VARIABLE
===================================================================*/
static DayTime_typedef Watch;
static DayTime_typedef SetTimer;

static unsigned char GetButton1;
static unsigned char GetButton2;

static volatile unsigned char Time_Mode;
static volatile unsigned char FlagStart;
static volatile unsigned char FlagHG;  
static volatile unsigned char FlagLedAlarm;

static unsigned char Data_Read[20];
static volatile unsigned int Length_Data_Read;

static unsigned char SelectMenu;
static unsigned char SelectPosition;

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
  SelectMenu=0;
  SelectPosition=0;
  GetButton1=0;
  GetButton2=0;
  FlagLedAlarm=0;
}

static void LED_BLINK_CONFIG(void)
{
  WritePin(PORTC,PIN13,LOW);
  Delay_TIM2_ms(200);
  WritePin(PORTC,PIN13,HIGH);
  Delay_TIM2_ms(200);
  WritePin(PORTC,PIN13,LOW);
  Delay_TIM2_ms(200);
  WritePin(PORTC,PIN13,HIGH);
  Delay_TIM2_ms(200); 

  WritePin(PORTC,PIN13,LOW);
  Delay_TIM2_ms(1000);
  WritePin(PORTC,PIN13,HIGH);   
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

static unsigned char CheckRuleTime(DayTime_typedef *Time)
{
  unsigned char Result=FALSE;

  if(Time_Mode == AM) /* 1->12->1 */
  {
    if( (Time->Hour>=1) && (Time->Hour<=12) ) Result=TRUE;
  }
  else /* PM: 1->23->0->1 */
  {
    if( (Time->Hour>=0) && (Time->Hour<=23) ) Result=TRUE;
  }
  return Result;
}

static void Decode_Data(void)
{
  DayTime_typedef NewTime;
  unsigned char count=0;
  unsigned char TimeData[10];

  for(count=3; count<=8; count++)
  {
    TimeData[count] = Data_Read[count]-'0';
  }
  Link_Number(&NewTime.Hour, &TimeData[3], &TimeData[4]);
  Link_Number(&NewTime.Minute, &TimeData[5], &TimeData[6]);
  Link_Number(&NewTime.Second, &TimeData[7], &TimeData[8]);

  if( (Data_Read[1]=='S') && (Data_Read[2]=='T') ) /* START */
  {
    FlagStart=START; 
  }
  else 
  {
    if ( (Data_Read[1]=='H') && (Data_Read[2]=='G') )  /* Hen gio */
    {
      if(CheckRuleTime(&NewTime) == TRUE) 
      {
        FlagHG=HG;
        SetTimer = NewTime;
      }
    }
    else if ( (Data_Read[1]=='A') && (Data_Read[2]=='M') ) /* AM */
    {      
      if(CheckRuleTime(&NewTime) == TRUE) 
      {
        Time_Mode=AM;
        Watch = NewTime;
      }
    }
    else if ( (Data_Read[1]=='P') && (Data_Read[2]=='M') ) /* PM */
    {
      if(CheckRuleTime(&NewTime) == TRUE) 
      {
        Time_Mode=PM;
        Watch = NewTime;
      }
    }
    else {}
  }

}

static void LED_Alarm(void)
{
  TogglePin(PORTC,PIN13);
}

static void STOP_LED_Alarm(void)
{
  WritePin(PORTC,PIN13,HIGH);
  Softtimer_StopTimer(Softtimer_Alarm);
}

static void CheckAction_START(void)
{
  if( (Time_Mode==AM) || (Time_Mode==PM) )
  {
    if(FlagStart==START)
    {
      Softtimer_StartTimer(Softtimer_START,1000,CONTINUE,&Watch_Display);
    }
  }
}

static void CheckTIMER_Alarm(void)
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
        FlagLedAlarm=1;
        Softtimer_StartTimer(Softtimer_Alarm,1000,CONTINUE,&LED_Alarm);
        Step=1;
      }
    }
  }
  else
  {
    if(FlagLedAlarm==1) Step=0;
  }
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
        CheckAction_START();
        CheckFrame=0;
        Length_Data_Read=0;
      }

    }
    else Length_Data_Read=0;      
  }

}

static void LED_Blink(unsigned char Number)
{
  static unsigned int TickBlink=0;
  static unsigned char StepBlink=0;
  if(StepBlink==0)
  {
    LCD_TurnOff(Number);
    TickBlink = Tick_us;
    StepBlink=1;
  }
  else if(StepBlink==1)
  {
    if( (unsigned int)(Tick_us-TickBlink)>=(500*TickMicroSecond) )
    {
      if(SelectMenu==Menu_ConfigTime) LCD_TimeDisplay(Watch.Hour, Watch.Minute, Watch.Second);
      else LCD_TimeDisplay(SetTimer.Hour, SetTimer.Minute, SetTimer.Second);
      TickBlink = Tick_us;
      StepBlink=2;
    }
  }
  else
  {
    if( (unsigned int)(Tick_us-TickBlink)>=(500*TickMicroSecond) )
    {
      TickBlink = Tick_us;
      StepBlink=0;
    }
  }
  
}

static void SelectMainMenu(void)
{
  static unsigned int Tickbutton1=0;
  static unsigned int Tickbutton2=0;

  if(FlagStart==START)
  {
    if(GetButton1==0) /* Press hold Button 1 -> Set Watch */
    {
      if( (unsigned int)(Tick_us-Tickbutton1)>=(3000*TickMicroSecond) ) /* Nhan giu 3s */
      {
        LED_BLINK_CONFIG();

        if(SelectMenu==No_Menu_Select) SelectMenu=Menu_ConfigTime;
      }
      else 
      {
        if(FlagLedAlarm==1) STOP_LED_Alarm(); /* Neu Led hen gio dang ON -> OFF */
      } 
    }
    else Tickbutton1=Tick_us;

    if(GetButton2==0) /* Press hold Button 2 -> Set Alarm */
    {
      if( (unsigned int)(Tick_us-Tickbutton2)>=(3000*TickMicroSecond) ) /* Nhan giu 3s */
      {
        LED_BLINK_CONFIG();

        if(SelectMenu==No_Menu_Select) 
        {
          SelectMenu=Menu_TimerAlarm;
          LCD_TimeDisplay(SetTimer.Hour, SetTimer.Minute, SetTimer.Second);
        }
      }
      else 
      {
        if(FlagLedAlarm==1) STOP_LED_Alarm(); /* Neu Led hen gio dang ON -> OFF */
      } 
    }
    else Tickbutton2=Tick_us;

  }
}

static unsigned char SelectBabyMenu(DayTime_typedef *Time, unsigned char *NumberPos)
{
  unsigned char Result=FALSE;
  static unsigned int Tickbutton=0;
  static char LastButton1=1;
  static char LastButton2=1;

  if( (GetButton1==0)&&(GetButton2==0) )
  {
    if( (unsigned int)(Tick_us-Tickbutton)>=(3000*TickMicroSecond) ) /* Nhan giu 3s */
    {
      LED_BLINK_CONFIG();
      Result=TRUE;
      SelectPosition=SelectPos;
    }
  }
  else 
  {
    Tickbutton=Tick_us;

    if(GetButton1!=LastButton1) /* Press button 1 */
    {
      if(GetButton1==0)
      {
        if(*NumberPos>=7) *NumberPos=1;
        else *NumberPos+=3;
      }
      LastButton1=GetButton1;
    }

    if(GetButton2!=LastButton2) /* Press button 2 */
    {
      if(GetButton2==0)
      {
        if(*NumberPos==1) 
        {
          if(Time->Second>=59) Time->Second=0;
          else Time->Second++;
        }
        else if(*NumberPos==4)
        {
          if(Time->Minute>=59) Time->Minute=0;
          else Time->Minute++;
        }
        else
        {
          if(Time_Mode==AM)
          {
            if(Time->Hour>=12) Time->Hour=1;
            else Time->Hour++;
          }
          else 
          {
            if(Time->Hour>=23) Time->Hour=0;
            else Time->Hour++;            
          }

        }
      }
      LastButton2=GetButton2;
    }
  }

  return Result;
}

static void MAIN_MENU(void)
{
  static unsigned char PosNumber=1;
  static unsigned char StepChoice=0;

  if(SelectMenu==No_Menu_Select) SelectMainMenu();

  if(SelectMenu==Menu_ConfigTime) /* Menu time config */
  {
    if(StepChoice==0) /* STOP Softtimer Watch */
    {
      Softtimer_StopTimer(Softtimer_START);
      StepChoice=1;
    }
    else if(StepChoice==1) /* Choice position number */
    {
      LED_Blink(PosNumber);
      if( SelectBabyMenu(&Watch,&PosNumber)==TRUE )
      {
        if(SelectPosition==SelectPos) StepChoice=2;
      }
      
    }
    else 
    {
      Softtimer_StartTimer(Softtimer_START,1000,CONTINUE,&Watch_Display);
      SelectMenu=No_Menu_Select;
      PosNumber=1;
      StepChoice=0;
    }
  }
  else if(SelectMenu==Menu_TimerAlarm) /* Menu hen gio */
  {
    if(StepChoice==0) /* Choice position number */
    {
      LED_Blink(PosNumber);
      if( SelectBabyMenu(&SetTimer,&PosNumber)==TRUE )
      {
        if(SelectPosition==SelectPos) StepChoice=1;
      }
      
    }
    else 
    {
      SelectMenu=No_Menu_Select;
      PosNumber=1;
      StepChoice=0;
    }
  }
  else  /* LED Display */
  {
    LCD_TimeDisplay(Watch.Hour, Watch.Minute, Watch.Second);
  }
}

static void ACTION(void)
{
  Check_Data_UART();
  CheckTIMER_Alarm();
  
  MAIN_MENU();
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
    GetButton1 = (unsigned char)ReadPin(PORTA,PIN2);
    GetButton2 = (unsigned char)ReadPin(PORTA,PIN3);

    if( Uart_GetReceiveState()==NOT_EMP )
    {
      Length_Data_Read = Uart_GetReceiveData(Data_Read);
    }
    else 
    {
      ACTION();
    }
    
    Softtimer_MainFunction();
    Uart_TxMainFunction();
    Delay_TIM2_ms(2);
  }

}
/*=================================================================*/


