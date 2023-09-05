
#ifndef __APP_FUNCTION__ 
#define __APP_FUNCTION__ 

#include "STM32F1XX.h"

typedef struct
{
  unsigned char Hour;
  unsigned char Minute;
  unsigned char Second;
  unsigned char Day;
  unsigned char Month;
  unsigned char Year;
}DayTime_typedef;

typedef enum 
{
  ZERO,
  AM,
  PM,
  HG,
  START
}TimeMode_enum;

void MAIN_APP(void)__attribute__ ((noreturn));

#endif /* __APP_FUNCTION__ */


